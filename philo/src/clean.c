/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:20:31 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/19 16:27:58 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutex(t_data *data)
{
	t_philo	*tmp;
	int		i;

	tmp = NULL;
	i = 0;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		if (i++ < data->count_mutex)
			pthread_mutex_destroy(&tmp->mutex_fork);
		tmp = tmp->next;
	}
	if (data->count_mutex == data->n_philo + 1)
		pthread_mutex_destroy(&data->mutex_print);
	if (data->count_mutex == data->n_philo + 2)
		pthread_mutex_destroy(&data->mutex_dead);
	destroy_philo(data);
}

void	destroy_thread(t_data *data)
{
	t_philo	*tmp;

	tmp = data->philo;
	while (data->count_thread > data->n_eat)
	{
		pthread_join(tmp->thread_supervisor, NULL);
		tmp = tmp->next;
	}
	tmp = data->philo;
	while (data->count_thread > 0)
	{
		pthread_join(tmp->thread_philo, NULL);
		tmp = tmp->next;
	}
	destroy_mutex(data);
}

void	destroy_philo(t_data *data)
{
	t_philo *tmp;
	t_philo *next;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		next = tmp->next;
		if (tmp)
		{
			free(tmp);
			tmp = NULL;
		}
		tmp = next;
	}
}