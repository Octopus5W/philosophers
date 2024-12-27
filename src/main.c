#include "../philo.h"

int is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
void	check_settings(t_data data)
{
	if (data.n_philo < 1)
		write(2, "Error: number of philosophers must be at least 1\n", 50);
	if (data.t_die < 60)
		write(2, "Error: time to die must be at least 60ms\n", 41);
	if (data.n_eat < 60)
		write(2, "Error: time to eat must be at least 60ms\n", 41);
	if (data.t_sleep < 60)
		write(2, "Error: time to sleep must be at least 60ms\n", 43);
	if (data.n_eat < 0 && data.n_eat != -1)
		write(2, "Error: number of times each philosopher must eat must be positive or must be non-existent\n", 70);
	if (data.n_philo < 1 || data.t_die < 1 || data.t_eat < 1 || data.t_sleep < 1 || (data.n_eat < 0 && data.n_eat != -1))
		exit(1);
}

void	data_clear(t_data *data)
{
	printf("destroy_philo %d\n", data->n_philo);
}



// void	set_thread(t_data *data)
// {
// 	int i;

// 	i = 0;
// 	while (i < data->n_philo)
// 	{
// 		if (pthread_create(&data->philo->thread, NULL, &routine, &data->philo))
// 		{
// 			write(2, "Error: pthread_create failed in set_thread\n", 43);
// 			data_clear(data);
// 			exit(1);
// 		}
// 		i++;
// 	}
// }


int is_dead(t_philo *philo)
{
	if (philo->is_dead)
	{
		printf("philo %d is dead\n", philo->id);
		exit(1);
	}
	return (0);
}

void	philo_eat(t_philo *philo)
{
	if (!is_dead(philo))
	{
		printf("philo %d is eating\n", philo->id);
	}
}

void philo_think(t_philo *philo)
{
	if (!is_dead(philo))
	{
		printf("philo %d is thinking\n", philo->id);
	}
}

void	philo_sleep(t_philo *philo)
{
	if (!is_dead(philo))
	{
		printf("philo %d is sleeping\n", philo->id);
	}
}
void	take_fork(t_philo *philo)
{
	if (philo->fork == 1 && (philo->prev->fork == 1 || philo->next->fork == 1))
	{
		philo->fork = 2;
		if (philo->prev->fork == 1)
			philo->prev->fork = 0;
		else if (philo->next->fork == 1)
			philo->next->fork = 0;
		printf("philo %d has taken a fork\n", philo->id);
		philo_eat(philo);
		philo->fork = 1;
		if (philo->prev->fork == 0)
			philo->prev->fork = 1;
		else if (philo->next->fork == 0)
			philo->next->fork = 1;
		philo_sleep(philo);
		philo_think(philo);
		exit(1);
	}
	else
		philo_think(philo);
}

void *routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo*)arg;
	if (!is_dead(philo))
		take_fork(philo);
	else
	{
		printf("philo %d is dead\n", philo->id);
		exit(1);
	}
	return(NULL);
}

void	set_philo(t_data *data)
{
	int i;
	t_philo *tmp;
	t_philo *first;

	if (data->n_philo)
		data->n_philo = -1;
	i = data->n_philo;

	tmp = NULL;
	// if (!data->philo)
	// {
	// 	write(2, "Error: malloc failed in set_philo\n", 21);
	// 	destroy_philo(philo, (i - 1));
	// 	exit(1);
	// }
	while (i--)
	{
		data->philo = malloc(sizeof(t_philo));
		if (tmp)
			tmp->next = data->philo;
		if (i + 1 == data->n_philo)
			first = data->philo;
		pthread_mutex_init(&data->philo->mutex, NULL);
		pthread_create(&data->philo->thread, NULL, &routine, &data->philo);
		data->philo->id = i;
		data->philo->fork = 1;
		data->philo->is_dead = 0;
		data->philo->is_eating = 0;
		data->philo->is_sleeping = 0;
		data->philo->is_thinking = 0;
		data->philo->n_eat = 0;
		data->philo->prev = tmp;
		tmp = data->philo;
	}
	data->philo->next = first;
	first->prev = data->philo;
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
	return (0);
}
