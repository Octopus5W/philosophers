/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/16 12:01:15 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_fork(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork);
	print_message("has taken a fork", data->mutex_print, philo);
	pthread_mutex_lock(&philo->next->mutex_fork);
	print_message("has taken a fork", data->mutex_print, philo);
}

void	philo_eat(t_data *data, t_philo *philo)
{
	print_message("is eating", data->mutex_print, philo);
	philo->t_die += philo->t_die;
	my_sleep(data->t_eat);
	pthread_mutex_unlock(&philo->next->mutex_fork);
	pthread_mutex_unlock(&philo->mutex_fork);
}
void	philo_sleep(t_data *data, t_philo *philo)
{
	print_message("is sleeping", data->mutex_print, philo);
	my_sleep(data->t_sleep);
}
void	philo_think(t_data *data, t_philo *philo)
{
	print_message("is thinking", data->mutex_print, philo);
}
// void	check_dead(t_data *data, t_philo *philo);