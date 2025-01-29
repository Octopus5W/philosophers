/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:39 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/01/29 12:00:26 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_ms(t_data *data)
{
	struct timeval	current_time;
	long			time;

	gettimeofday(&current_time, NULL);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	time -= (data->current_time.tv_sec * 1000) + \
	(data->current_time.tv_usec / 1000);
	return (time);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		take_fork(philo->data, philo);
		philo_eat(philo->data, philo);
		philo_sleep(philo->data, philo);
		philo_think(philo->data, philo);
		if (philo->data->is_dead || philo->data->n_eat == 0)
			exit(1);
	}
	return (NULL);
}

t_philo*	set_philo(t_data *data)
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
	first->prev = data->philo;
	return(data->philo->next = first);
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
	if (pthread_mutex_init(&data->mutex_dead, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_print, NULL))
		return (1);
	return (0);
}

void	set_thread(t_data *data)
{
	t_philo	*tmp;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		tmp->last_meal = 0;
		if (pthread_create(&tmp->thread, NULL, &routine, tmp))
		{
			write(2, "Error: pthread_create failed in set_thread\n", 43);
			exit(1);
		}
		tmp = tmp->next;
	}
	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next;
	}
		
}

void print_philo(t_data *data)
{
	t_philo	*tmp;

	tmp = NULL;
	while (tmp != data->philo)
	{
		if (tmp == NULL)
			tmp = data->philo;
		printf("philo %d\n", tmp->id);
		tmp = tmp->next;
	}
}

int	main(int ac, char *av[])
{
	t_data	data;

	check_settings(&data, ac, av);
	data.philo = set_philo(&data);
	set_mutex(&data);
	// gettimeofday(&data.current_time, NULL);
	// set_thread(&data);
	return (0);
}
