/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:27:20 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/20 10:15:05 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	get_ms(void)
{
	struct timeval	current_time;
	long			time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (printf("gettimeofday error"), -1);
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	my_sleep(long usec, t_data *data)
{
	usec *= 1000;
	while (usec > 0 && !data->is_dead)
	{
		usleep(1000);
		usec -= 1000;
	}
}

void	print_message(char *str, t_philo *philo)
{
	long	t_current;

	pthread_mutex_lock(&philo->data->mutex_print);
	if (philo->data->is_dead == 0 && str[0] != 'd')
	{
		t_current = get_ms();
		printf("%ld %i %s\n", t_current - philo->data->t_reference, philo->id,
			str);
		if (str[3] == 'e')
		{
			philo->n_eat++;
			check_eat(philo);
			philo->t_die += philo->data->t_die;
			philo->last_meal = t_current;
		}
	}
	else if (philo->data->is_dead == 0)
	{
		t_current = get_ms();
		printf("%ld %i %s\n", t_current - philo->data->t_reference, philo->id,
			str);
		philo->data->is_dead = 1;
	}
	pthread_mutex_unlock(&philo->data->mutex_print);
}

void	check_eat(t_philo *philo)
{
	if (philo->n_eat == philo->data->n_eat)
		philo->data->has_eat++;
	if (philo->data->has_eat == philo->data->n_philo)
		is_dead(philo);
}
