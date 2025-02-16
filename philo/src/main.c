/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/16 12:15:21 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// void	print_philo(t_data *data) // delete before last push
// {
// 	t_philo *tmp;

// 	tmp = NULL;
// 	while (tmp != data->philo)
// 	{
// 		if (tmp == NULL)
// 			tmp = data->philo;
// 		tmp = tmp->next;
// 	}
// }
int	check_dead(t_philo *philo)
{
	if (philo->last_meal)
}

void	superpower(void *arg)
{
	t_data	*data;
	int		*count_eat;

	data = (t_data *)arg;
	while (data->is_dead == 0)
	{
		if (data->philo->t_die <= data->reference_time - get_ms())
		{
			print_message("is dead", data->mutex_print, data->philo);
			break ;
		}
		data->philo = data->philo->next;
	}
}

int	create_supervisor(t_data *data)
{
	pthread_create(&data->supervisor, NULL, &superpower, data);
	pthread_detach(&data->supervisor);
}

int	main(int ac, char *av[])
{
	t_data	data;

	check_settings(&data, ac, av);
	data.philo = set_philo(&data);
	data.is_dead = 0;
	if (set_mutex(&data))
		return (1);
	data.reference_time = get_ms();
	if (data.reference_time == -1)
		return (1);
	if (create_supervisor(&data))
		return (1);
	if (set_thread(&data))
		return (1);
	return (0);
}
