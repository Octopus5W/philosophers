/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/07 16:12:24 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*superpower(void *arg)
{
	t_data	*data;
	t_philo	*tmp;
	long	time;

	data = (t_data *)arg;
	tmp = data->philo;
	usleep(10000);
	while (1)
	{
		pthread_mutex_lock(&data->mutex_dead);
		time = get_ms();
		if ((tmp->t_die && time >= tmp->t_die) || data->is_dead)
		{
			print_die("die", tmp);
			pthread_mutex_unlock(&data->mutex_dead);
			break ;
		}
		pthread_mutex_unlock(&data->mutex_dead);
		usleep(300);
		tmp = tmp->next;
	}
	return (NULL);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->t_die = philo->data->t_reference + philo->data->t_die;
	pthread_mutex_unlock(&philo->data->mutex_dead);
	while (1)
	{
		if (is_dead(philo->data))
			break ;
		take_fork(philo);
		philo_eat(philo->data, philo);
		philo_sleep(philo->data, philo);
		philo_think(philo);
	}
	return (NULL);
}

void	*routine_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->t_die = philo->data->t_reference + philo->data->t_die;
	pthread_mutex_unlock(&philo->data->mutex_dead);
	pthread_mutex_lock(&philo->mutex_fork);
	print_message("has taken a fork", philo);
	my_sleep(get_ms(), philo->data->t_eat);
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
