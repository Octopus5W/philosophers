/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:54 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/01/11 20:08:02 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	check_settings(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		exit(1);
	}
	if (!is_digit(av[1]) || !is_digit(av[2]) || !is_digit(av[3])
		|| !is_digit(av[4]) || (ac == 6 && !is_digit(av[5])))
	{
		write(2, "Error: arguments must be positive integers\n", 43);
		exit(1);
	}
	data->n_philo = atoi(av[1]);
	data->t_die = atoi(av[2]);
	data->t_eat = atoi(av[3]);
	data->t_sleep = atoi(av[4]);
	if (ac == 6)
		data->n_eat = atoi(av[5]);
	else
		data->n_eat = -1;
	if (data->t_die < 60)
		write(2, "Error: time to die must be at least 60ms\n", 41);
	if (data->t_eat < 60)
		write(2, "Error: time to eat must be at least 60ms\n", 41);
	if (data->t_sleep < 60)
		write(2, "Error: time to sleep must be at least 60ms\n", 43);
}
