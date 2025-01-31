/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 06:33:41 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 03:21:27 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int init_philos(t_simulation *sim, int i)
{
	while (++i < sim->num_philo)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].last_eat_time = 0;
		sim->philosophers[i].start_time = 0;
		sim->philosophers[i].to_starvation = sim->t2die;
		sim->philosophers[i].times_eaten = 0;
		sim->philosophers[i].is_dead = 0;
		sim->philosophers[i].is_fin = 0;
		sim->philosophers[i].data = sim;
		if (init_philo_mutexes(&sim->philosophers[i]) != 0)
		{
			while (i > 0)
			{
				pthread_mutex_destroy(&sim->philosophers[--i].starvation_mtx);
				pthread_mutex_destroy(&sim->philosophers[i].times_eaten_mtx);
				pthread_mutex_destroy(&sim->philosophers[i].dead_mtx);
				pthread_mutex_destroy(&sim->philosophers[i].fin_mtx);
			}
			while (sim->num_philo > 0)
				pthread_mutex_destroy(&sim->forks[--sim->num_philo]);
			return (1);
		}
	}
	return (0);
}
/* 
-- init fork mutex
-- set pointer in philo strucure 
*/
static int	init_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (pthread_mutex_init(&sim->forks[i++], NULL) != 0)
		{
			while (i > 0)
				pthread_mutex_destroy(&sim->forks[--i]);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < sim->num_philo)
	{
		sim->philosophers[i].right = &sim->forks[i];
		sim->philosophers[i].left = &sim->forks[(i + 1) % sim->num_philo];
		if (sim->num_philo == 1)
			sim->philosophers[i].left = NULL;
		i++;
	}
	return (0);
}
/* threads = philos + monitor */
static int	allocation(t_simulation *sim)
{
	sim->forks = malloc((sizeof(pthread_mutex_t) * sim->num_philo));
	sim->threads = malloc((sizeof(pthread_t) * sim->num_philo + 1));
	sim->philosophers = malloc((sizeof(t_philosopher) * sim->num_philo));
	if (!sim->forks || !sim->threads || !sim->philosophers)
		return (1);
	return (0);
}
/*
-- SET PARAMS
-- VALIDATE PARAMS
*/
static int	init_simulation(t_simulation *sim, char **param)
{
	sim->num_philo = ft_atoi(param[1]);
	sim->t2die = ft_atoll(param[2]);
	sim->t2eat = ft_atoll(param[3]);
	sim->t2sleep = ft_atoll(param[4]);
	sim->is_stop = 0;
	sim->died_logged = 0;
	if (param[5])
		sim->must_eat_count = ft_atoi(param[5]);
	else
		sim->must_eat_count = -1;
	if (sim->num_philo <= 0 || sim->num_philo > 200
		|| sim->t2die < 0 || sim->t2eat < 0 || sim->t2sleep < 0)
		return (1);
	if (init_sim_mutexes(sim))
		return (1);
	return (0);
}

int	ft_philo_init(t_simulation *sim, char **av)
{
	set_null(sim);
	if (init_simulation(sim, av))
		return (ft_error("[31mFAILED[0m: INIT" , sim, 0));
	if (allocation(sim))
		return (ft_error("[31mFAILED[0m: MALLOC" , sim, 0));
	if (init_forks(sim))
		return (ft_error("[31mFAILED[0m: SETUP_FORK" , sim, 0));
	if (init_philos(sim, -1))
		return (ft_error("[31mFAILED[0m: SETUP_PHILO" , sim, 0));
	return (0);
}
