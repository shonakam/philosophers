/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:06:23 by shonakam          #+#    #+#             */
/*   Updated: 2025/01/31 22:34:53 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

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
	philo->start_time = get_time();
	if (philo->id % 2 != 0)
			usleep(200);
			
	// log_action(philo, philo->id, "debug before init to_starv");
	pthread_mutex_lock(&philo->starvation_mtx);
	philo->to_starvation = philo->start_time + philo->data->t2die;
	pthread_mutex_unlock(&philo->starvation_mtx);
	// log_action(philo, philo->id, "debug before roop");

	while (!is_stop(philo))
	{
		routine_handler(philo);
		// log_action(philo, philo->id, "\033[33m debug \033[0m");

		if (philo->data->must_eat_count > 0 && philo->times_eaten >= philo->data->must_eat_count)
		{
			pthread_mutex_lock(&philo->fin_mtx);
			philo->is_fin = 1;
			pthread_mutex_unlock(&philo->fin_mtx);
		}
	}
	return ((void *)0);
}


/*
-- sim->threds[n] -> monitor
-- sim->threds[0 ~ n - 1] -> philo
-- failed pattern: ESRCH, EINVAL, EDEADLK
*/
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
			pthread_join(sim->threads[n], NULL);
			return (ft_error("[31mFAILED[0m: THREAD PHILO", sim, 1));
		}
		i++;
	}
	if (pthread_create(&sim->threads[n], NULL, &monitor, sim) != 0)
		return (ft_error("[31mFAILED[0m: THREAD MONITOR", sim, 1));
	i = 0;
	while (i <= n)
		pthread_join(sim->threads[i++], NULL);
	return (0);
}

