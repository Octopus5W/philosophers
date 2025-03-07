/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/07 17:49:50 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->next->mutex_fork);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(&philo->mutex_fork);
		print_message("has taken a fork", philo);
	}
	else
	{
		pthread_mutex_lock(&philo->mutex_fork);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(&philo->next->mutex_fork);
		print_message("has taken a fork", philo);
	}
}

void	philo_eat(t_data *data, t_philo *philo)
{
	print_message("is eating", philo);
	my_sleep(get_ms(), data->t_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->mutex_fork);
		pthread_mutex_unlock(&philo->next->mutex_fork);
	}
	else
	{
		pthread_mutex_unlock(&philo->next->mutex_fork);
		pthread_mutex_unlock(&philo->mutex_fork);
	}
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	print_message("is sleeping", philo);
	my_sleep(get_ms(), data->t_sleep);
}

void	philo_think(t_philo *philo)
{
	print_message("is thinking", philo);
}

int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->mutex_dead);
	if (data->is_dead)
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
