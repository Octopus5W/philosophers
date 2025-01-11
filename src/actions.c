#include "../philo.h"

void	take_fork(t_philo *philo)
{
	if (!philo->data->is_dead && philo->fork == 1 && philo->next->fork == 1)
	{
		philo->fork = 2;
		philo->next->fork = 0;
		printf("philo %d has taken a fork\n", philo->id);
	}
}

void	philo_eat(t_data *data, t_philo *philo)
{
	if (!data->is_dead)
	{
		printf("philo %d is eating\n", philo->id);
		philo->fork = 1;
		philo->next->fork = 1;
		usleep(data->t_eat * 1000);
		philo->n_eat++;
	}
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	if (!data->is_dead)
	{
		printf("philo %d is sleeping\n", philo->id);
		usleep(data->t_sleep * 1000);
	}
}

void philo_think(t_data *data, t_philo *philo)
{
	if (!data->is_dead)
	{
		printf("philo %d is thinking\n", philo->id);
		if(pthread_join(philo->next->thread, NULL))
		{
			if (data->is_dead)
				exit(1);
		}
	}
}

void philo_die(t_data *data, t_philo *philo)
{
	t_philo *ptr;

	if (!data->is_dead)
	{
		data->is_dead = 1;
		ptr = philo;
		while (philo->next != ptr)
		{
			pthread_join(philo->next->thread, NULL);
			philo = philo->next;
		}
		printf("philo %d is dead\n", ptr->id);
		exit(1);
	}
	exit(1);
}
