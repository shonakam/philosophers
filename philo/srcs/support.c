/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:30:34 by shonakam          #+#    #+#             */
/*   Updated: 2025/01/31 22:35:19 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static int	is_dead(t_philosopher *philo)
{
	int stop;

	pthread_mutex_lock(&philo->data->stop_mtx);
	pthread_mutex_lock(&philo->dead_mtx);
	stop = philo->data->is_stop;
	pthread_mutex_unlock(&philo->dead_mtx);
	pthread_mutex_unlock(&philo->data->stop_mtx);

	if (stop)
	{
		printf("<== HERE IS STOP ==>\n");
		return (1);
	}
	return (0);
}

void	log_action(t_philosopher *philo, int id, const char *action)
{
	if (is_dead(philo))
		return ;
	pthread_mutex_lock(&philo->data->diedlog_mtx);
	pthread_mutex_lock(&philo->dead_mtx);
	pthread_mutex_lock(&philo->starvation_mtx);
	id++;
	if (!philo->is_dead && !philo->data->died_logged)
		printf("%lld %d %s\n", get_time() - philo->start_time, id, action);
	if (philo->is_dead && !philo->data->died_logged)
	{
		printf("%lld %d %s\n", get_time() - philo->start_time, id, action);
		philo->data->died_logged = 1;
	}
	pthread_mutex_unlock(&philo->starvation_mtx);
	pthread_mutex_unlock(&philo->dead_mtx);
	pthread_mutex_unlock(&philo->data->diedlog_mtx);
}

void	routine_handler(t_philosopher *philo)
{
	controller_take(philo);
	controller_eat(philo);
	log_action(philo, philo->id, "\033[33m debug \033[0m");
	controller_put(philo);
	controller_sleep(philo);
	controller_think(philo);
}
