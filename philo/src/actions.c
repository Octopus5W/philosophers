/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:45 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/01/28 07:27:46 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	pthread_mutex_lock(&philo->next->mutex_fork);
	pthread_mutex_lock(&data->mutex_dead);
	if (!philo->data->is_dead && philo->fork == 1 && philo->next->fork == 1)
	{
		philo->fork = 2;
		philo->next->fork = 0;
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->next->mutex_fork);
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld philo %d has taken a fork\n", get_ms(data), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	else
	{
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->next->mutex_fork);
		pthread_mutex_unlock(&data->mutex_dead);
	}
}

void	philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead)
	{
		pthread_mutex_lock(&philo->mutex_fork);
		pthread_mutex_lock(&philo->next->mutex_fork);
		pthread_mutex_lock(&philo->data->mutex_print);
		philo->fork = 1;
		philo->next->fork = 1;
		philo->last_meal = get_ms(data);
		printf("%ld philo %d is eating\n", philo->last_meal, philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		usleep(data->t_eat * 1000);
		philo->n_eat++;
	}
	else
		pthread_mutex_unlock(&data->mutex_dead);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&data->mutex_print);
		philo->last_sleep = get_ms(data);
		printf("%ld philo %d is sleeping\n", philo->last_sleep, philo->id);
		usleep(data->t_sleep * 1000);
		pthread_mutex_unlock(&data->mutex_print);
	}
	else
		pthread_mutex_unlock(&data->mutex_dead);
}

void	philo_think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&data->mutex_print);
		printf("%ld philo %d is thinking\n", get_ms(data), philo->id);
		pthread_mutex_unlock(&data->mutex_print);
	}
	else
		pthread_mutex_unlock(&data->mutex_dead);
}

void	philo_die(t_data *data, t_philo *philo)
{
	if (!data->is_dead && \
	(get_ms(data) - philo->last_meal - philo->last_sleep) > data->t_die)
	{
		data->is_dead = 1;
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld philo %d is dead\n", get_ms(data), philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		pthread_mutex_unlock(&data->mutex_dead);
		exit(1);
	}
	else if (data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		exit(1);
	}
}
