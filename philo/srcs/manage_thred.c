/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_thred.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 14:06:23 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/28 15:33:26 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	monitor_sup(t_simulation *sim)
{
	int				i;
	int				finished_count;

	finished_count = 0;
	i = 0;
	while (i < sim->num_philo)
	{
		if (sim->philosophers[i].is_dead)
		{
			sim->is_stop = 1;
			return (1);
		}
		if (sim->philosophers[i].is_fin)
			finished_count++;
		i++;
	}
	if (finished_count == sim->num_philo)
	{
		sim->is_stop = 1;
		return (1);
	}
	return (0);
}

static void	*monitor(void *arg)
{
	t_simulation	*sim;

	sim = (t_simulation *)arg;
	while (1)
	{
		pthread_mutex_lock(&sim->lock);
		if (monitor_sup(sim))
		{
			pthread_mutex_unlock(&sim->lock);
			return (NULL);
		}
		pthread_mutex_unlock(&sim->lock);
		usleep(10000);
	}
	return ((void *)0);
}

/* starvation check every 10ms */
static void	*observer(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	while (!philo->is_dead)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (get_time() - philo->data->t2die > philo->to_starvation && philo->data->t2die != philo->to_starvation)
		{
			philo->is_dead = 1;
			log_action(philo, philo->id, "\033[31mdied\033[0m");
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (philo->times_eaten >= philo->data->must_eat_count)
			return (NULL);
		usleep(10000);
	}
	return (NULL);
}

static void	*routine(void *arg)
{
	t_philosopher	*philo;
	pthread_t		observer_t;

	philo = (t_philosopher *)arg;
	if (pthread_create(&observer_t, NULL, &observer, (void *)philo))
		return ((void *)1);
	philo->start_time = get_time();
	while (!philo->is_dead && !philo->is_fin && !philo->data->is_stop)
	{
		routine_handler(philo);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->must_eat_count > 0
			&& philo->times_eaten >= philo->data->must_eat_count)
		{
			philo->is_fin = 1;
			log_action(philo, philo->id, "\033[32mfinished\033[0m");
		}
		pthread_mutex_unlock(&philo->data->lock);
	}
	if (pthread_join(observer_t, NULL))
		return ((void *)1);
	return ((void *)0);
}

/*
-- sim->threds[n] -> monitor
-- sim->threds[0 ~ n - 1] -> philo
-- failed pattern: ESRCH, EINVAL, EDEADLK
*/
int	start_simulation(t_simulation *sim)
{
	int	i;
	int	n;

	n = sim->num_philo;
	if (pthread_create(&sim->threads[n], NULL, &monitor, sim) != 0)
		return (ft_error("[31mFAILED[0m: THRED MONITOR" , sim, 1));
	i = 0;
	while (i < n)
	{
		if (pthread_create(&sim->threads[i], NULL,
			&routine, &sim->philosophers[i]) != 0)
		{
			while (i > 0)
				pthread_join(sim->threads[--i], NULL);
			pthread_join(sim->threads[n], NULL);
			return (ft_error("[31mFAILED[0m: THRED PHILO", sim, 1));
		}
		usleep(100);
		i++;
	}
	i = 0;
	while (i <= n)
		pthread_join(sim->threads[i++], NULL);
	return (0);
}
