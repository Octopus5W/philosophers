/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/20 09:55:39 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*superpower(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_ms() < philo->t_die && !philo->data->is_dead)
		usleep(500);
	if (philo->t_die > philo->last_meal)
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		if (!philo->data->is_dead)
			print_message("die", philo);
		pthread_mutex_unlock(&philo->data->mutex_dead);
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->t_die = philo->data->t_reference + philo->data->t_die;
	if (pthread_create(&philo->thread_supervisor, NULL, &superpower, philo))
		return (NULL);
	philo->data->count_thread++;
	while (!philo->data->is_dead)
		take_fork(philo->data, philo);
	pthread_join(philo->thread_supervisor, NULL);
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
	destroy_philo(&data);
	return (0);
}
