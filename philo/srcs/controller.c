/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:49:13 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 03:21:35 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	controller_think(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	log_action(philo, philo->id, "is thinking");
}

void	controller_take(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	pthread_mutex_lock(philo->right);
	log_action(philo, philo->id, "has taken a fork");
	pthread_mutex_lock(philo->left);
	log_action(philo, philo->id, "has taken a fork");
}

void	controller_eat(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	log_action(philo, philo->id, "is eating");
	wraped_sleep(philo->data->t2eat * 1000);
	pthread_mutex_lock(&philo->starvation_mtx);
	philo->last_eat_time = get_time();
	philo->to_starvation = philo->last_eat_time + philo->data->t2die;
	pthread_mutex_unlock(&philo->starvation_mtx);
	philo->times_eaten++;
}

void	controller_put(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	controller_sleep(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	log_action(philo, philo->id, "is sleeping");
	wraped_sleep(philo->data->t2sleep * 1000);
}
