/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:30:34 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 02:32:56 by shonakam         ###   ########.fr       */
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

void	routine_handler(t_philosopher *philo)
{
	controller_take(philo);
	controller_eat(philo);
	controller_put(philo);
	controller_sleep(philo);
	controller_think(philo);
}

void set_null(t_simulation *sim)
{
	if (!sim)
		return;
	sim->forks = NULL;
	sim->threads = NULL;
	sim->philosophers = NULL;
	sim->num_philo = 0;
	sim->t2die = 0;
	sim->t2eat = 0;
	sim->t2sleep = 0;
	sim->must_eat_count = -1;
	sim->is_stop = 0;
	sim->died_logged = 0;
	sim->monitor_ready = 0;
}
