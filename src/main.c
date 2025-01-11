#include "../philo.h"

void *routine(void *arg)
{
	t_philo *philo;

	printf("routine\n");

	philo = (t_philo*)arg;
	take_fork(philo);
	philo_eat(philo->data, philo);
	philo_sleep(philo->data, philo);
	philo_think(philo->data, philo);
	if (philo->data->is_dead)
		exit(1);
	return (NULL);
}

void	set_philo(t_data *data)
{
	int i;
	t_philo *tmp;
	t_philo *first;

	i = -1;
	while (++i < data->n_philo)
	{
		data->philo = malloc(sizeof(t_philo));
		if (tmp)
			tmp->next = data->philo;
		if (i == 0)
			first = data->philo;
		data->philo->id = i + 1;
		data->philo->fork = 1;
		data->philo->is_eating = 0;
		data->philo->is_sleeping = 0;
		data->philo->is_thinking = 0;
		data->philo->n_eat = 0;
		data->philo->prev = tmp;
		tmp = data->philo;
		pthread_mutex_init(&data->philo->mutex, NULL);
		data->philo->data = data;
	}
	data->philo->next = first;
	first->prev = data->philo;
}

void set_thread(t_data *data)
{
	t_philo *tmp;

	tmp = data->philo;
	do
	{
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
		{
			write(2, "Error: pthread_create failed in set_thread\n", 43);
			exit(1);
		}
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	} while (tmp != data->philo);
}


int main (int ac, char* av[])
{
	t_data data;

	if (ac < 5 || ac > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		exit(1);
	}
	if (!is_digit(av[1]) || !is_digit(av[2]) || !is_digit(av[3]) || !is_digit(av[4]) || (ac == 6 && !is_digit(av[5])))
	{
		write(2, "Error: arguments must be positive integers\n", 43);
		exit(1);
	}	
	data.n_philo = atoi(av[1]);
	data.t_die = atoi(av[2]);
	data.t_eat = atoi(av[3]);
	data.t_sleep = atoi(av[4]);
	if (ac == 6)
		data.n_eat = atoi(av[5]);
	else
		data.n_eat = -1;
	check_settings(data);
	set_philo(&data);
	set_thread(&data);
	return (0);
}
