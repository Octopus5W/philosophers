/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 19:27:20 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/04 19:59:29 by hdelbecq         ###   ########.fr       */
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

void	my_sleep(long t_reference, long msec, t_data *data)
{
	long	t_end;

	t_end = t_reference + msec;
	while (get_ms() < t_end)
	{
		if (is_dead(data))
			break ;
		usleep(200);
	}
}

void	print_message(char *str, t_philo *philo)
{
	long	t_current;

	if (str[0] != 'd' && !is_dead(philo->data))
	{
		t_current = get_ms();
		printf("%ld %i %s\n", t_current - philo->data->t_reference, philo->id,
			str);
		if (str[3] == 'e')
		{
			philo->t_die += philo->data->t_die;
			philo->n_eat++;
			check_eat(philo);
		}
	}
	else if (str[0] == 'd')
	{
		philo->data->is_dead = 1;
		t_current = get_ms();
		printf("%ld %i %s\n", t_current - philo->data->t_reference, philo->id,
			str);
	}
}

void	check_eat(t_philo *philo)
{
	if (philo->n_eat == philo->data->n_eat)
		philo->data->has_eat++;
	if (philo->data->has_eat == philo->data->n_philo)
	{
		philo->data->is_dead = 1;
	}
}
