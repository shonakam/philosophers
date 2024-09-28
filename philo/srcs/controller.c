/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:49:13 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/28 18:06:14 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

void	controller_think(t_philosopher *philo)
{
	if (!philo->left)
	{
		// usleep(philo->data->t2die * 1000);
		// philo->is_dead = 1;
		// philo->data->is_stop = 1;
		// log_action(philo, philo->id, "\033[31mdied\033[0m");
		return ;
	}
	if (philo->id != 0 && philo->id % 2 != 0)
	{
		log_action(philo, philo->id, "is thinking");
		usleep(200);
	}
}

void	controller_take(t_philosopher *philo)
{
	pthread_mutex_lock(philo->right);
	log_action(philo, philo->id, "has taken a right fork");
	if (!philo->left)
		return ;
	pthread_mutex_lock(philo->left);
	log_action(philo, philo->id, "has taken a left fork");
}

void	controller_eat(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	log_action(philo, philo->id, "is eating");
	wraped_sleep(philo->data->t2eat * 1000);
	philo->last_eat_time = get_time();
	philo->to_starvation = philo->last_eat_time + philo->data->t2die;
	philo->times_eaten++;
}

void	controller_put(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right);
	if (!philo->left)
		return ;
	pthread_mutex_unlock(philo->left);
}

void	controller_sleep(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	log_action(philo, philo->id, "is sleeping");
	wraped_sleep(philo->data->t2sleep * 1000);
}
