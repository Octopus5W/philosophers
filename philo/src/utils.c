/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:27:20 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/08 14:50:43 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_ms(void)
{
	struct timeval	current_time;
	long			time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (printf("gettimeofday error\n"), -1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	my_sleep(long t_reference, long msec)
{
	long	t_end;

	t_end = t_reference + msec;
	while (get_ms() < t_end)
		usleep(50);
}

void	print_message(char *str, t_philo *philo)
{
	if (!is_dead(philo->data))
	{
		pthread_mutex_lock(&philo->data->mutex_print);
		printf("%ld %i %s\n", get_ms() - philo->data->t_reference, philo->id,
			str);
		pthread_mutex_unlock(&philo->data->mutex_print);
		if (str[3] == 'e')
			check_eat(philo);
	}
}

void	print_die(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_print);
	if (!philo->data->is_dead)
	{
		philo->data->is_dead = 1;
		printf("%ld %i %s\n", get_ms() - philo->data->t_reference, philo->id,
			str);
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->mutex_dead);
	philo->t_die = get_ms() + philo->data->t_die;
	philo->n_eat++;
	if (philo->n_eat == philo->data->n_eat)
		philo->data->has_eat++;
	if (philo->data->has_eat == philo->data->n_philo)
		philo->data->is_dead = 1;
	pthread_mutex_unlock(&philo->data->mutex_dead);
}
