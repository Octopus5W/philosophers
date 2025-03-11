/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:20:54 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/11 15:52:17 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *s)
{
	int	i;
	int	nb;

	nb = 0;
	i = 0;
	while (s && ((s[i] >= 9 && s[i] <= 13) || s[i] == 32))
	{
		s++;
	}
	if (s[i] == '+')
		s++;
	if (!s[i])
		return (-1);
	while (s[i] >= '0' && s[i] <= '9')
	{
		nb = nb * 10 + s[i] - 48;
		s++;
	}
	if (s[i])
		return (-1);
	return (nb);
}

int	ft_ctoi(char c)
{
	return (c - 48);
}

int	int_max(char *str, int lenght)
{
	if (lenght == 10 && str[0] != '+')
	{
		if (ft_ctoi(str[0]) <= 2 && ft_ctoi(str[1]) <= 1 && ft_ctoi(str[2]) <= 4
			&& ft_ctoi(str[3]) <= 7 && ft_ctoi(str[4]) <= 4
			&& ft_ctoi(str[5]) <= 8 && ft_ctoi(str[6]) <= 3
			&& ft_ctoi(str[7]) <= 6 && ft_ctoi(str[8]) <= 4
			&& ft_ctoi(str[9]) <= 7)
		{
			return (0);
		}
	}
	else if (lenght < 10 || (lenght == 10 && str[0] != '+'))
		return (0);
	return (1);
}

int	is_integer(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '+')
			i++;
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	if (int_max(str, i))
		return (0);
	return (1);
}

void	check_settings(t_data *data, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		write(2, "Error: wrong number of arguments\n", 34);
		exit(1);
	}
	if (!is_integer(av[1]) || !is_integer(av[2]) || !is_integer(av[3])
		|| !is_integer(av[4]) || (ac == 6 && !is_integer(av[5])))
	{
		write(2, "Error: arguments must be positive integers\n", 43);
		exit(1);
	}
	data->n_philo = ft_atoi(av[1]);
	data->t_die = ft_atoi(av[2]);
	data->t_eat = ft_atoi(av[3]);
	data->t_sleep = ft_atoi(av[4]);
	if (data->n_philo < 1 || data->n_philo > 200 || data->t_die < 60
		|| data->t_eat < 60 || data->t_sleep < 60)
	{
		write(2, "Error: philo must be between 0 and 201, time over 60\n", 53);
		exit(1);
	}
	if (ac == 6)
		data->n_eat = ft_atoi(av[5]);
	else
		data->n_eat = -1;
}
