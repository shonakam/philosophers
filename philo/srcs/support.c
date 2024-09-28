/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   support.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 14:30:34 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/28 15:29:41 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	log_action(t_philosopher *philo, int id, const char *action)
{
	if (philo->data->is_stop)
		return ;
	pthread_mutex_lock(&philo->data->log_mutex);
	printf("%lld %d %s\n", get_time(), id, action);
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
	pthread_mutex_lock(&philo->data->lock);
	controller_eat(philo);
	pthread_mutex_unlock(&philo->data->lock);
	controller_put(philo);
	controller_sleep(philo);
}
void	wraped_sleep(long long time)
{
	long long	start;

	if (time <= 0)
		return ;
	start = get_time();
	time *= 1000;
	while ((get_time() - start) < (time / 1000))
		usleep(time / 10);
}
