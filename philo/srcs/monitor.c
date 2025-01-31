/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:18:01 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 05:04:10 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int check_starvation_and_death(t_simulation *sim)
{
	int i = 0;
	
	while (i < sim->num_philo)
	{
		pthread_mutex_lock(&sim->philosophers[i].starvation_mtx);
		if (get_time() > sim->philosophers[i].to_starvation &&
			sim->philosophers[i].to_starvation != sim->t2die)
		{
			pthread_mutex_lock(&sim->philosophers[i].dead_mtx);
			sim->philosophers[i].is_dead = 1;
			pthread_mutex_unlock(&sim->philosophers[i].dead_mtx);
			log_died(&sim->philosophers[i], 
				sim->philosophers[i].id, "\033[31mdied\033[0m");
			pthread_mutex_unlock(&sim->philosophers[i].starvation_mtx);

			pthread_mutex_lock(&sim->stop_mtx);
			sim->is_stop = 1;
			pthread_mutex_unlock(&sim->stop_mtx);
			return (1);
		}
		pthread_mutex_unlock(&sim->philosophers[i].starvation_mtx);
		i++;
	}
	return (0);
}

static int check_all_finished(t_simulation *sim)
{
	int	i;
	int	finished_count;

	i = 0;
	finished_count = 0;
	while (i < sim->num_philo)
	{
		pthread_mutex_lock(&sim->philosophers[i].fin_mtx);
		if (sim->philosophers[i].is_fin)
			finished_count++;
		pthread_mutex_unlock(&sim->philosophers[i].fin_mtx);
		i++;
	}
	if (finished_count == sim->num_philo)
	{
		pthread_mutex_lock(&sim->stop_mtx);
		sim->is_stop = 1;
		pthread_mutex_unlock(&sim->stop_mtx);
		return (1);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;

	while (1)
	{
		if (check_starvation_and_death(sim) || check_all_finished(sim))
		{
			break ;
		}
		wraped_sleep(10000);
	}
	return (NULL);
}
