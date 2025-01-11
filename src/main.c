/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/01/11 20:58:50 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	printf("routine\n");
	philo = (t_philo *)arg;
	take_fork(philo);
	philo_eat(philo->data, philo);
	philo_sleep(philo->data, philo);
	philo_think(philo->data, philo);
	if (philo->data->is_dead)
		exit(1);
	return (NULL);
}

void	set_philo(t_data *data)
{
	int		i;
	t_philo	*tmp;
	t_philo	*first;

	i = -1;
	tmp = NULL;
	while (++i < data->n_philo)
	{
		data->philo = malloc(sizeof(t_philo));
		if (tmp)
			tmp->next = data->philo;
		if (i == 0)
			first = data->philo;
		data->philo->id = i + 1;
		data->philo->fork = 1;
		data->philo->is_eating = 0;
		data->philo->is_sleeping = 0;
		data->philo->is_thinking = 0;
		data->philo->n_eat = 0;
		data->philo->prev = tmp;
		tmp = data->philo;
		data->philo->data = data;
	}
	data->philo->next = first;
	first->prev = data->philo;
}

void	set_thread(t_data *data)
{
	t_philo	*tmp;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		pthread_mutex_init(&data->philo->mutex, NULL);
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
		{
			write(2, "Error: pthread_create failed in set_thread\n", 43);
			exit(1);
		}
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
}

int	main(int ac, char *av[])
{
	t_data	data;

	check_settings(&data, ac, av);
	set_philo(&data);
	set_thread(&data);
	printf("thread set\n");
	return (0);
}
