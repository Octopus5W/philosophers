/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_program.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/18 16:13:46 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_philo	*set_philo(t_data *data)
{
	int		i;
	t_philo	*tmp;
	t_philo	*first;

	i = -1;
	tmp = NULL;
	while (++i < data->n_philo)
	{
		data->philo = malloc(sizeof(t_philo)); // check error
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
	return (data->philo->next = first);
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
			return (1);
		tmp = tmp->next;
	}
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (1);
	return (0);
}

int	set_thread(t_data *data)
{
	t_philo	*tmp;
	long	ms;

	tmp = NULL;
	if ((ms = get_ms()) == -1)
		return (1);
	data->t_reference = ms;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		if (pthread_create(&tmp->thread_philo, NULL, &routine, tmp))
			return (write(2, "Error: pthread_create failed in set_thread\n",
					43), 1);
		tmp = tmp->next;
	}
	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		pthread_join(tmp->thread_philo, NULL);
		tmp = tmp->next;
	}
	return (0);
}
