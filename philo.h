#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_philo
{
	int id;
	int fork;
	int is_eating;
	int is_sleeping;
	int is_thinking;
	int n_eat;
	pthread_mutex_t mutex;
	pthread_t thread;
	struct s_data *data;
	struct s_philo *prev;
	struct s_philo *next;
} t_philo;

typedef struct s_data
{
	int n_philo;
	int n_eat;
	int t_die;
	int t_eat;
	int t_sleep;
	int is_dead;
	t_philo *philo;
} t_data;

int is_digit(char *str);
void check_settings(t_data data);

void take_fork(t_philo *philo);
void philo_eat(t_data *data, t_philo *philo);
void philo_sleep(t_data *data, t_philo *philo);
void philo_think(t_data *data, t_philo *philo);
void philo_die(t_data *data, t_philo *philo);

 #endif
 