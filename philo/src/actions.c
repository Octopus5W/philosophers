/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/17 19:23:36 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	print_message("has taken a fork", philo);
	pthread_mutex_lock(&philo->next->mutex_fork);
	print_message("has taken a fork", philo);
	philo_eat(data, philo);
}

void	philo_eat(t_data *data, t_philo *philo)
{
	print_message("is eating", philo);
	philo->n_eat++;
	my_sleep(data->t_eat, data);
	pthread_mutex_unlock(&philo->next->mutex_fork);
	pthread_mutex_unlock(&philo->mutex_fork);
	philo_sleep(data, philo);
}
void	philo_sleep(t_data *data, t_philo *philo)
{
	print_message("is sleeping", philo);
	my_sleep(data->t_sleep, data);
	philo_think(philo);
}
void	philo_think(t_philo *philo)
{
	print_message("is thinking", philo);
}