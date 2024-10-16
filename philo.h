#ifndef PHILO_H
#define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct status
{
	int id;
	int is_dead;
	int is_eating;
	int is_sleeping;
	int is_thinking;
	int n_eat;
} t_status;

typedef struct s_philo
{
	int n_philo;
	int n_eat;
	int t_die;
	int t_eat;
	int t_sleep;
	t_status *status;
} t_philo;

 #endif
