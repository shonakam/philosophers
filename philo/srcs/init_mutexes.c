/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mutexes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:59:19 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 01:05:23 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	init_sim_mutexes(t_simulation *sim)
{
	if (pthread_mutex_init(&sim->diedlog_mtx, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&sim->stop_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->diedlog_mtx);
		return (1);
	}
	if (pthread_mutex_init(&sim->monitor_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&sim->stop_mtx);
		pthread_mutex_destroy(&sim->diedlog_mtx);
		return (1);
	}
	return (0);
}
int	init_philo_mutexes(t_philosopher *philo)
{
	if (pthread_mutex_init(&philo->starvation_mtx, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->times_eaten_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->starvation_mtx);
		return (1);
	}
	if (pthread_mutex_init(&philo->dead_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->times_eaten_mtx);
		pthread_mutex_destroy(&philo->starvation_mtx);
		return (1);
	}
	if (pthread_mutex_init(&philo->fin_mtx, NULL) != 0)
	{
		pthread_mutex_destroy(&philo->dead_mtx);
		pthread_mutex_destroy(&philo->times_eaten_mtx);
		pthread_mutex_destroy(&philo->starvation_mtx);
		return (1);
	}
	return (0);
}

