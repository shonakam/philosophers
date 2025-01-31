/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:06:23 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 04:40:03 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	standby(t_philosopher *philo)
{
	int	f;

	f = 1;
	while (f)
	{
		pthread_mutex_lock(&philo->data->monitor_mtx);
		if (philo->data->monitor_ready == 1)
			f = 0;
		pthread_mutex_unlock(&philo->data->monitor_mtx);
		wraped_sleep(10);
	}
}

static int is_stop(t_philosopher *philo)
{
	int dead;
	int fin;
	int	stop;
	
	pthread_mutex_lock(&philo->dead_mtx);
	dead = philo->is_dead;
	pthread_mutex_unlock(&philo->dead_mtx);
	pthread_mutex_lock(&philo->fin_mtx);
	fin = philo->is_fin;
	pthread_mutex_unlock(&philo->fin_mtx);
	pthread_mutex_lock(&philo->data->stop_mtx);
	stop = philo->data->is_stop;
	pthread_mutex_unlock(&philo->data->stop_mtx);
	if (dead || fin || stop)
		return (1);
	return (0);
}

static void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	standby(philo);
	philo->start_time = get_time();
	if (philo->id % 2 != 0)
		wraped_sleep(200);
	pthread_mutex_lock(&philo->starvation_mtx);
	philo->to_starvation = philo->start_time + philo->data->t2die;
	pthread_mutex_unlock(&philo->starvation_mtx);
	while (!is_stop(philo))
	{
		routine_handler(philo);
		if (philo->data->must_eat_count > 0 &&
			philo->times_eaten >= philo->data->must_eat_count)
		{
			pthread_mutex_lock(&philo->fin_mtx);
			philo->is_fin = 1;
			pthread_mutex_unlock(&philo->fin_mtx);
		}
	}
	pthread_mutex_unlock(philo->right);
	return ((void *)0);
}

int	start_simulation(t_simulation *sim, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&sim->threads[i], NULL, &routine, &sim->philosophers[i]) != 0)
		{
			while (i > 0)
				pthread_join(sim->threads[--i], NULL);
			return (ft_error("[31mFAILED[0m: THREAD PHILO", sim));
		}
		i++;
	}
	if (pthread_create(&sim->threads[n], NULL, &monitor, sim) != 0)
		return (ft_error("[31mFAILED[0m: THREAD MONITOR", sim));
	pthread_mutex_lock(&sim->monitor_mtx);
	sim->monitor_ready = 1;
	pthread_mutex_unlock(&sim->monitor_mtx);
	return (0);
}

