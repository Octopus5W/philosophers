/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:20:31 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/01 18:38:25 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	destroy_mutex(t_data *data)
{
	t_philo	*tmp;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		pthread_mutex_destroy(&tmp->mutex_fork);
		tmp = tmp->next;
	}
	pthread_mutex_destroy(&data->mutex_dead);
	pthread_mutex_destroy(&data->mutex_print);
}

void	destroy_thread(t_data *data)
{
	t_philo	*tmp;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
}

void	destroy_philo(t_data *data)
{
	t_philo *tmp;
	t_philo *tmp2;

	tmp = data->philo;
	while (tmp != data->philo)
	{
		tmp2 = tmp;
		tmp = tmp->next;
		free(tmp2);
	}
}