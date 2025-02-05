/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:21:00 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/05 09:46:29 by hdelbecq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	int				fork;
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				n_eat;
	long			last_meal;
	long			last_sleep;
	pthread_mutex_t	mutex_fork;
	pthread_t		thread;
	struct s_data	*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				n_eat;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				is_dead;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_print;
	t_philo			*philo;
	struct timeval	current_time;
}					t_data;

int					take_fork(t_data *data, t_philo *philo);
void				philo_eat(t_data *data, t_philo *philo);
void				philo_sleep(t_data *data, t_philo *philo);
void				philo_think(t_data *data, t_philo *philo);
int					check_dead(t_data *data, t_philo *philo);

void				destroy_mutex(t_data *data);
void				destroy_thread(t_data *data);
void				destroy_philo(t_data *data);

int					is_digit(char *str);
void				check_settings(t_data *data, int ac, char **av);

void				my_sleep(int time);

long				get_ms(t_data *data);
#endif
