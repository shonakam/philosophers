/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 03:21:46 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 13:10:53 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	free_all(t_simulation *sim)
{
	if (sim->forks)
	{
		free(sim->forks);
		sim->forks = NULL;
	}
	if (sim->philosophers)
	{
		free(sim->philosophers);
		sim->philosophers = NULL;
	}
	if (sim->threads)
	{
		free(sim->threads);
		sim->threads = NULL;
	}
}

void	cleanup(t_simulation *sim)
{
	int	i;

	if (!sim)
		return ;
	if (sim->threads)
	{
		i = 0;
		while (i <= sim->num_philo)
		{
			if (sim->threads[i])
				pthread_join(sim->threads[i], NULL);
			i++;
		}
	}
	pthread_mutex_destroy(&sim->diedlog_mtx);
	pthread_mutex_destroy(&sim->stop_mtx);
	pthread_mutex_destroy(&sim->monitor_mtx);
	free_all(sim);
}
