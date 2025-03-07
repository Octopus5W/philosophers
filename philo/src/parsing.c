/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:54 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/07 18:03:02 by hdelbecq         ###   ########.fr       */
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
	if (i > 3)
		return (0);
	return (1);
}

int	ft_atoi(const char *s)
{
	int	nb;
	int	sign;

	sign = 1;
	nb = 0;
	while (*s && ((*s >= 9 && *s <= 13) || *s == 32))
	{
		s++;
	}
	if (*s == '-')
	{
		sign = -1;
		s++;
	}
	else if (*s == '+')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		nb = nb * 10 + *s - 48;
		s++;
	}
	return (nb * sign);
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
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->n_eat = atoi(av[5]);
	else
		data->n_eat = -1;
}
