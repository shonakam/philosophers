/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:11 by shonakam          #+#    #+#             */
/*   Updated: 2025/01/31 22:08:50 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

int	ft_error(const char *message, void *data, int f)
{
	printf("%s\n", message);
	if (data)
		cleanup((t_simulation *)data, f);
	return (1);
}

static void	free_all(t_simulation *sim)
{
	if (sim->forks)
		free(sim->forks);
	if (sim->philosophers)
		free(sim->philosophers);
	if (sim->threads)
		free(sim->threads);
}

void	cleanup(t_simulation *sim, int f)
{
	int	i;

	i = 0;
	while (f && i < sim->num_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philosophers[i].dead_mtx);
		pthread_mutex_destroy(&sim->philosophers[i].starvation_mtx);
		i++;
	}
	pthread_mutex_destroy(&sim->diedlog_mtx);
	pthread_mutex_destroy(&sim->stop_mtx);
	free_all(sim);
}
