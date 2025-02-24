/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/24 21:41:21 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*superpower(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (!data->philo->t_die || (get_ms() < data->philo->t_die
			&& !data->is_dead))
		data->philo = data->philo->next;
	if (data->philo->t_die > data->philo->last_meal)
	{
		pthread_mutex_lock(&data->mutex_dead);
		if (!data->is_dead)
			print_message("die", data->philo);
		pthread_mutex_unlock(&data->mutex_dead);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->t_die = philo->data->t_reference + philo->data->t_die;
	philo->data->count_thread++;
	while (!philo->data->is_dead)
	{
		take_fork(philo->data, philo);
		philo_eat(philo->data, philo);
		philo_sleep(philo->data, philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->t_die = philo->data->t_reference + philo->data->t_die;
	pthread_mutex_lock(&philo->mutex_fork);
	print_message("has taken a fork", philo);
	while (!philo->data->is_dead)
		usleep(500);
	pthread_mutex_unlock(&philo->mutex_fork);
	return (NULL);
}

int	main(int ac, char *av[])
{
	t_data	data;

	data.is_dead = 0;
	data.has_eat = 0;
	data.count_mutex = 0;
	data.count_thread = 0;
	check_settings(&data, ac, av);
	if (set_philo(&data))
		destroy_philo(&data);
	if (set_mutex(&data))
		return (destroy_mutex(&data), 1);
	if (set_thread(&data))
		return (destroy_philo(&data), 1);
	destroy_thread(&data);
	return (0);
}
