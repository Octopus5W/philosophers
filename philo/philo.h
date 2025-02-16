/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:21:00 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/02/16 11:59:05 by hdelbecq         ###   ########.fr       */
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
	int				is_eating;
	int				is_sleeping;
	int				is_thinking;
	int				n_eat;
	long			last_meal;
	long			last_sleep;
	long			t_die;
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
	long			t_eat;
	long			t_sleep;
	long			t_die;
	int				is_dead;
	long			reference_time;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_print;
	t_philo			*philo;
	pthread_t		supervisor;

	struct timeval	time;
}					t_data;

int					is_digit(char *str);
void				check_settings(t_data *data, int ac, char **av);

void				take_fork(t_data *data, t_philo *philo);
void				philo_eat(t_data *data, t_philo *philo);
void				philo_sleep(t_data *data, t_philo *philo);
void				philo_think(t_data *data, t_philo *philo);
void				check_dead(t_data *data, t_philo *philo);

void				destroy_mutex(t_data *data);
void				destroy_thread(t_data *data);
void				destroy_philo(t_data *data);

t_philo				*set_philo(t_data *data);
int					set_mutex(t_data *data);
int					set_thread(t_data *data);
void				*routine(void *arg);

long				get_ms(void);
void				my_sleep(long usec);
void				print_message(char *str, pthread_mutex_t mutex,
						t_philo *philo);
#endif
