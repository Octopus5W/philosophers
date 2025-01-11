#include "../philo.h"

int is_digit(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	check_settings(t_data data)
{
	if (data.n_philo < 1)
		write(2, "Error: number of philosophers must be at least 1\n", 50);
	if (data.t_die < 60)
		write(2, "Error: time to die must be at least 60ms\n", 41);
	if (data.n_eat < 60)
		write(2, "Error: time to eat must be at least 60ms\n", 41);
	if (data.t_sleep < 60)
		write(2, "Error: time to sleep must be at least 60ms\n", 43);
	if (data.n_eat < 0 && data.n_eat != -1)
		write(2, "Error: number of times each philosopher must eat must be positive or must be non-existent\n", 70);
	if (data.n_philo < 1 || data.t_die < 1 || data.t_eat < 1 || data.t_sleep < 1 || (data.n_eat < 0 && data.n_eat != -1))
		exit(1);
}
