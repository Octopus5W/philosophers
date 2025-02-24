/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/24 21:43:55 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_data *data, t_philo *philo)
{
	if (philo->id % 2 == 1)
	{
		pthread_mutex_lock(&philo->next->mutex_fork);
		print_message("has taken a fork", philo);
		pthread_mutex_lock(&philo->mutex_fork);
		print_message("has taken a fork", philo);
		philo_eat(data, philo);
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
	my_sleep(data->t_eat, data);
	pthread_mutex_unlock(&philo->next->mutex_fork);
	pthread_mutex_unlock(&philo->mutex_fork);
}

void	philo_sleep(t_data *data, t_philo *philo)
{
	print_message("is sleeping", philo);
	my_sleep(data->t_sleep, data);
}

void	philo_think(t_philo *philo)
{
	print_message("is thinking", philo);
}

void	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->data->is_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex_dead);
}
