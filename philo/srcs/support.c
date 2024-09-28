/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:30:34 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/28 18:32:29 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	log_action(t_philosopher *philo, int id, const char *action)
{
	if (philo->data->is_stop)
		return;
	pthread_mutex_lock(&philo->data->log_mutex);
	if (!philo->is_dead && !philo->data->died_logged)
		printf("%lld %d %s\n", get_time() - philo->start_time, id, action);
	if (philo->is_dead && !philo->data->died_logged)
	{
		printf("%lld %d %s\n", get_time() - philo->start_time, id, action);
		philo->data->died_logged = 1;
	}
	pthread_mutex_unlock(&philo->data->log_mutex);
}

int	is_dead(t_philosopher *philo)
{
	if (philo->start_time == 0)
		return (0);
	else if (philo->last_eat_time == 0 
		&& get_time() > philo->to_starvation)
		return (1);
	else if (get_time() > philo->to_starvation)
		return (1);
	return (0);
}
void	routine_handler(t_philosopher *philo)
{
	controller_think(philo);
	controller_take(philo);
	// pthread_mutex_lock(&philo->lock);
	controller_eat(philo);
	// pthread_mutex_unlock(&philo->lock);
	controller_put(philo);
	controller_sleep(philo);
}
