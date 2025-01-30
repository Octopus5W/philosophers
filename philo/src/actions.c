/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:45 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/01/30 11:12:31 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_fork(t_data *data, t_philo *philo)
{
	if (!check_dead(data,philo)) 
	{
		pthread_mutex_lock(&philo->mutex_fork);
		pthread_mutex_lock(&philo->next->mutex_fork);
		if(philo->fork == 1 && philo->next->fork == 1)
		{
			philo->next->fork = 0;
			pthread_mutex_unlock(&philo->next->mutex_fork);
			philo->fork = 2;
			pthread_mutex_unlock(&philo->mutex_fork);
			pthread_mutex_lock(&philo->data->mutex_print);
			printf("%ld philo %d has taken a fork\n", get_ms(data), philo->id);
			pthread_mutex_unlock(&philo->data->mutex_print);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&philo->next->mutex_fork);
			pthread_mutex_unlock(&philo->mutex_fork);
			return (0);
		}
	}
	return (0);
}

void	philo_eat(t_data *data, t_philo *philo)
{	
	
	if (!check_dead(data, philo))
	{
		pthread_mutex_lock(&philo->mutex_fork);
		pthread_mutex_lock(&philo->next->mutex_fork);
		if (philo->fork == 2)
		{
			pthread_mutex_lock(&philo->data->mutex_print);
			philo->last_meal = get_ms(data);
			printf("%ld philo %d is eating\n", philo->last_meal, philo->id);
			pthread_mutex_unlock(&philo->data->mutex_print);
			
			usleep(data->t_eat * 1000);
			if (data->n_eat != -1)
				philo->n_eat++;
			philo->next->fork = 1;
			pthread_mutex_unlock(&philo->next->mutex_fork);
			philo->fork = 1;
			pthread_mutex_unlock(&philo->mutex_fork);
		}
	}
	else
	{
		pthread_mutex_unlock(&philo->next->mutex_fork);
		pthread_mutex_unlock(&philo->mutex_fork);	
	}
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	if (!check_dead(data, philo))
	{
		pthread_mutex_lock(&data->mutex_print);
		philo->last_sleep = get_ms(data);
		printf("%ld philo %d is sleeping\n", philo->last_sleep, philo->id);
		pthread_mutex_unlock(&data->mutex_print);
		usleep(data->t_sleep * 1000);
	}
}

void	philo_think(t_data *data, t_philo *philo)
{
	if (!check_dead(data, philo))
	{
		pthread_mutex_lock(&data->mutex_print);
		printf("%ld philo %d is thinking\n", get_ms(data), philo->id);
		pthread_mutex_unlock(&data->mutex_print);
		while (philo->n_eat < philo->data->n_eat || philo->data->n_eat == -1)
		{	
			if (check_dead(data, philo))
				break;
			else if (take_fork(philo->data, philo))
			{
				philo_eat(philo->data, philo);
				philo_sleep(philo->data, philo);
			}
			usleep(10);
		}
	}
}

int	check_dead(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead && \
	(get_ms(data) - philo->last_meal - philo->last_sleep) > data->t_die)
	{
		data->is_dead = 1;
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld philo %d is dead\n", get_ms(data), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		pthread_mutex_unlock(&data->mutex_dead);
		return(1);
	}
	else if (data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&data->mutex_dead);
		return (0);	
	}
}
