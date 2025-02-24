/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/25 00:30:53 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	set_philo(t_data *data)
{
	int		i;
	t_philo	*tmp;
	t_philo	*first;

	i = -1;
	tmp = NULL;
	while (++i < data->n_philo)
	{
		data->philo = malloc(sizeof(t_philo));
		if (!data->philo)
			return (write(2, "Error: Malloc\n", 14), --i);
		if (tmp)
			tmp->next = data->philo;
		if (i == 0)
			first = data->philo;
		data->philo->id = i + 1;
		data->philo->n_eat = 0;
		data->philo->prev = tmp;
		data->philo->data = data;
		tmp = data->philo;
	}
	first->prev = data->philo;
	data->philo->next = first;
	data->philo = first;
	return (0);
}

int	set_mutex(t_data *data)
{
	t_philo	*tmp;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		if (pthread_mutex_init(&tmp->mutex_fork, NULL))
			return (write(2, "Error: mutex\n", 13), 1);
		data->count_mutex++;
		tmp = tmp->next;
	}
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (write(2, "Error: mutex\n", 13), 1);
	data->count_mutex++;
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (write(2, "Error: mutex\n", 13), 1);
	data->count_mutex++;
	return (0);
}

int	set_thread(t_data *data)
{
	data->t_reference = get_ms();
	if (pthread_create(&data->thread_supervisor, NULL, &superpower, data))
		return (write(2, "Error: pthread_create\n", 22), 1);
	data->count_thread++;
	if (set_thread_philo(data))
		return (write(2, "Error: pthread_create\n", 22), 1);
	return (0);
}

int	set_thread_philo(t_data *data)
{
	t_philo	*tmp;

	if (data->n_philo == 1)
	{
		tmp = data->philo;
		if (pthread_create(&tmp->thread_philo, NULL, &routine_one_philo, tmp))
			return (write(2, "Error: pthread_create\n", 22), 1);
		data->count_thread++;
	}
	else
	{
		tmp = NULL;
		while (tmp != data->philo)
		{
			if (tmp == NULL)
				tmp = data->philo;
			if (pthread_create(&tmp->thread_philo, NULL, &routine, tmp))
				return (write(2, "Error: pthread_create\n", 22), 1);
			data->count_thread++;
			tmp = tmp->next;
		}
	}
	return (0);
}
