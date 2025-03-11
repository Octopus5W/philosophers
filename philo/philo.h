/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelbecq <hdelbecq@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 16:21:00 by hdelbecq          #+#    #+#             */
/*   Updated: 2025/03/11 15:24:09 by hdelbecq         ###   ########.fr       */
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
	int				n_eat;
	long			t_die;
	pthread_mutex_t	mutex_fork;
	pthread_t		thread_philo;
	struct s_data	*data;
	struct s_philo	*prev;
	struct s_philo	*next;
}					t_philo;

typedef struct s_data
{
	int				n_philo;
	int				n_eat;
	int				is_dead;
	int				has_eat;
	long			t_eat;
	long			t_sleep;
	long			t_die;
	long			t_reference;
	int				count_mutex;
	int				count_thread;
	pthread_mutex_t	mutex_print;
	pthread_mutex_t	mutex_dead;
	pthread_t		thread_supervisor;
	t_philo			*philo;
	struct timeval	time;
}					t_data;

int					is_digit(char *str);
void				check_settings(t_data *data, int ac, char **av);

void				take_fork(t_philo *philo);
void				philo_eat(t_data *data, t_philo *philo);
void				philo_sleep(t_data *data, t_philo *philo);
void				philo_think(t_philo *philo);
int					is_dead(t_data *data);

void				destroy_mutex(t_data *data);
void				destroy_thread(t_data *data);
void				destroy_philo(t_data *data);

int					set_philo(t_data *data);
int					set_mutex(t_data *data);
int					set_thread(t_data *data);
int					set_thread_philo(t_data *data);

void				*routine(void *arg);
void				*superpower(void *arg);
void				*routine_one_philo(void *arg);

long				get_ms(void);
void				my_sleep(long t_reference, long msec);
void				print_message(char *str, t_philo *philo);
void				check_eat(t_philo *philo);

#endif
