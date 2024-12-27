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
	int is_dead;
	int is_eating;
	int is_sleeping;
	int is_thinking;
	int n_eat;
	pthread_mutex_t mutex;
	pthread_t thread;
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
	t_philo *philo;
} t_data;

 #endif
