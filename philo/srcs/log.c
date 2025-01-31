/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 01:37:05 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 03:21:17 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	is_stop(t_philosopher *philo)
{
	int stop;

	pthread_mutex_lock(&philo->data->stop_mtx);
	stop = philo->data->is_stop;
	pthread_mutex_unlock(&philo->data->stop_mtx);

	return (stop);
}

void	log_died(t_philosopher *philo, int id, const char *action)
{
	id++;
	pthread_mutex_lock(&philo->data->diedlog_mtx);
	pthread_mutex_lock(&philo->dead_mtx);
	if (philo->is_dead && !philo->data->died_logged)
	{
		printf("%lld %d %s\n", get_time() - philo->start_time, id, action);
		philo->data->died_logged = 1;
	}
	pthread_mutex_unlock(&philo->dead_mtx);
	pthread_mutex_unlock(&philo->data->diedlog_mtx);
}

void log_action(t_philosopher *philo, int id, const char *action)
{
	id++;
	if (is_stop(philo))
		return ;
	pthread_mutex_lock(&philo->starvation_mtx);
	pthread_mutex_lock(&philo->data->diedlog_mtx);
	pthread_mutex_lock(&philo->dead_mtx);
	if (!philo->is_dead && !philo->data->died_logged)
		printf("%lld %d %s\n", get_time() - philo->start_time, id, action);
	pthread_mutex_unlock(&philo->dead_mtx);
	pthread_mutex_unlock(&philo->data->diedlog_mtx);
	pthread_mutex_unlock(&philo->starvation_mtx);
}
