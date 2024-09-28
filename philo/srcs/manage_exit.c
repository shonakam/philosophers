/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 18:07:11 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/28 14:40:19 by shonakam         ###   ########.fr       */
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
		pthread_mutex_destroy(&sim->philosophers[i].lock);
		i++;
	}
	pthread_mutex_destroy(&sim->log_mutex);
	pthread_mutex_destroy(&sim->lock);
	free_all(sim);
}
