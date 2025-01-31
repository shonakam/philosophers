/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 02:14:16 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 04:39:30 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <pthread.h> 
# include <semaphore.h>
# include "utils.h"

/* forward declaration */
typedef struct s_simulation t_simulation;

typedef struct	s_philosopher
{
	int					id;
	long long			last_eat_time;
	long long			start_time;
	long long			to_starvation;
	int					times_eaten;
	int					is_dead;
	int					is_fin;
	pthread_mutex_t		starvation_mtx;
	pthread_mutex_t		times_eaten_mtx;
	pthread_mutex_t		dead_mtx;
	pthread_mutex_t		fin_mtx;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	t_simulation		*data;
}				t_philosopher;

typedef struct	s_simulation
{
	int				num_philo;
	long long		t2die;
	long long		t2eat;
	long long		t2sleep;
	int				must_eat_count;
	int				is_stop;
	int				died_logged;
	pthread_t		*threads;
	t_philosopher	*philosophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	stop_mtx;
	pthread_mutex_t	diedlog_mtx;
	pthread_mutex_t	monitor_mtx;
	int				monitor_ready;
}				t_simulation;

// typedef struct

/* <=== PHILO_MANAGER ===> */
int				ft_error(const char *message, void *data);
void			cleanup(t_simulation *sim);
int				ft_philo_init(t_simulation *sim, char **av);
int				start_simulation(t_simulation *sim, int n);
void			*monitor(void *arg);

/* <=== CONTROLLER ===> */
void			controller_think(t_philosopher *philo);
void			controller_take(t_philosopher *philo);
void			controller_eat(t_philosopher *philo);
void			controller_put(t_philosopher *philo);
void			controller_sleep(t_philosopher *philo);
long long		get_time(void);
void			log_action(t_philosopher *philo, int id, const char *action);
void			log_died(t_philosopher *philo, int id, const char *action);

void			routine_handler(t_philosopher *philo);
void			wraped_sleep(long long time);
void			set_null(t_simulation *sim);
int				init_sim_mutexes(t_simulation *sim);
int				init_philo_mutexes(t_philosopher *philo);