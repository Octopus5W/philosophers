/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:45 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/01/14 18:44:55 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	pthread_mutex_lock(&data->mutex_dead);
	if (!philo->data->is_dead && philo->fork == 1 && philo->next->fork == 1)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		philo->fork = 2;
		philo->next->fork = 0;
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("philo %d has taken a fork\n", philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	else
		philo_die(data, philo);
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_eat(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("philo %d is eating\n", philo->id);
		philo->fork = 1;
		philo->next->fork = 1;
		usleep(data->t_eat * 1000);
		philo->n_eat++;
		pthread_mutex_unlock(&philo->data->mutex_print);
	}
	else
		philo_die(data, philo);
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&data->mutex_print);
		printf("philo %d is sleeping\n", philo->id);
		usleep(data->t_sleep * 1000);
		pthread_mutex_unlock(&data->mutex_print);
	}
	else
		philo_die(data, philo);
}

void	philo_think(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (!data->is_dead)
	{
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&data->mutex_print);
		printf("philo %d is thinking\n", philo->id);
		pthread_mutex_unlock(&data->mutex_print);
	}
	else
		philo_die(data, philo);
}

void	philo_die(t_data *data, t_philo *philo)
{
	if (!data->is_dead)
	{
		data->is_dead = 1;
		pthread_mutex_unlock(&data->mutex_dead);
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("philo %d is dead\n", philo->id);
		pthread_mutex_unlock(&philo->data->mutex_print);
		exit(1);
	}
	else
		pthread_mutex_unlock(&data->mutex_dead);
	exit(1);
}
