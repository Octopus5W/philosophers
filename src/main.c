#include "../philo.h"

void	check_settings(t_philo philo)
{
	if (philo.n_philo < 2)
		write(1, "Error: number of philosophers must be at least 2\n", 50);
	if (philo.t_die < 60)
		write(1, "Error: time to die must be at least 60ms\n", 41);
	if (philo.t_eat < 60)
		write(1, "Error: time to eat must be at least 60ms\n", 41);
	if (philo.t_sleep < 60)
		write(1, "Error: time to sleep must be at least 60ms\n", 43);
	if (philo.n_eat < 0 && philo.n_eat != -1)
		write(1, "Error: number of times each philosopher must eat must be positive or must be non-existent\n", 70);
	if (philo.n_philo < 0 || philo.t_die < 1 || philo.t_eat < 1 || philo.t_sleep < 1 || (philo.n_eat < 0 && philo.n_eat != -1))
		exit(1);
}

void	set_philo(t_philo *philo)
{
	int i;

	i = 0;
	philo->status = malloc(sizeof(t_status) * philo->n_philo);
	if (!philo->status)
	{
		write(1, "Error: malloc failed in set_philo\n", 21);
		exit(1);
	}
	while (i < philo->n_philo)
	{
		philo->status[i].id = i;
		philo->status[i].is_dead = 0;
		philo->status[i].is_eating = 0;
		philo->status[i].is_sleeping = 0;
		philo->status[i].is_thinking = 1;
		philo->status[i].n_eat = 0;
		i++;
	}
}

int main (int ac, char* av[])
{
	t_philo philo;

	if (ac < 5 || ac > 6)
	{
		write(1, "Error: wrong number of arguments\n", 34);
		exit(1);
	}
	philo.n_philo = atoi(av[1]);
	philo.t_die = atoi(av[2]);
	philo.t_eat = atoi(av[3]);
	philo.t_sleep = atoi(av[4]);
	if (ac == 6)
		philo.n_eat = atoi(av[5]);
	else
		philo.n_eat = -1;
	check_settings(philo);
	set_philo(&philo);
	return (0);
}