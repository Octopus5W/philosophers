/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:27:20 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/16 12:13:39 by hdelbecq         ###   ########.fr       */
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

void	my_sleep(long usec)
{
	while (usec > 0)
	{
		usleep(1000);
		usec -= 1000;
	}
}

void	print_message(char *str, pthread_mutex_t mutex, t_philo *philo)
{
	long ms;
	
	pthread_mutex_lock(&mutex);
	ms = get_ms();
	if (philo->data->is_dead == 0)
	{
		printf("%ld philo %i %s\n", ms - philo->data->reference_time, philo->id, str);
		if (str[3] == 'e')
			philo->last_meal == ms;
	}
	if (str[3] == 'd')
		philo->data->is_dead == 1;
	pthread_mutex_unlock(&mutex);
}
