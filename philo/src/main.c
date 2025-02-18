/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/18 19:20:59 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*superpower(void *arg)
{
	t_philo	*philo;
	long	ms;

	philo = (t_philo *)arg;
	while ((ms = get_ms()) < philo->t_die && ms != -1)
	{
		pthread_mutex_lock(&philo->data->mutex_dead);
		if (philo->data->is_dead)
		{
			pthread_mutex_unlock(&philo->data->mutex_dead);
			break ;
		}
		else
			pthread_mutex_unlock(&philo->data->mutex_dead);
	}
	if (ms == -1)
		return ((void *)1);
	if (philo->t_die > philo->last_meal && !philo->data->is_dead)
		print_message("is dead", philo);
	return ((void *)0);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->t_die = philo->data->t_reference + philo->data->t_die;
	if (pthread_create(&philo->thread_supervisor, NULL, &superpower, philo))
		return ((void *)1);
	while (!philo->data->is_dead)
		take_fork(philo->data, philo);
	pthread_join(philo->thread_supervisor, NULL);
	return ((void *)0);
}

int	main(int ac, char *av[])
{
	t_data	data;

	data.is_dead = 0;
	data.has_eat = 0;
	check_settings(&data, ac, av);
	data.philo = set_philo(&data);
	if (set_mutex(&data))
		return (1);
	if (set_thread(&data))
		return (1);
	return (0);
}
