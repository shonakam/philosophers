/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:49:13 by shonakam          #+#    #+#             */
/*   Updated: 2025/01/31 22:39:21 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

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
	
	// pthread_mutex_lock(&philo->data->diedlog_mtx);
	// printf("%d taked fork at %p(right)\n", philo->id, philo->right);
	// pthread_mutex_unlock(&philo->data->diedlog_mtx);

	pthread_mutex_lock(philo->left);
	log_action(philo, philo->id, "has taken a fork");
	
	// pthread_mutex_lock(&philo->data->diedlog_mtx);
	// printf("%d taked fork at %p(left)\n", philo->id, philo->left);
	// pthread_mutex_unlock(&philo->data->diedlog_mtx);
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
	// pthread_mutex_lock(&philo->data->diedlog_mtx);
	// printf("%d will put fork at %p(right)\n", philo->id, philo->right);
	// pthread_mutex_unlock(&philo->data->diedlog_mtx);
	
	pthread_mutex_unlock(philo->right);
	
	// pthread_mutex_lock(&philo->data->diedlog_mtx);
	// printf("%d will put fork at %p(left)\n", philo->id, philo->left);
	// pthread_mutex_unlock(&philo->data->diedlog_mtx);
	
	pthread_mutex_unlock(philo->left);
}

void	controller_sleep(t_philosopher *philo)
{
	if (!philo->left)
		return ;
	log_action(philo, philo->id, "is sleeping");
	wraped_sleep(philo->data->t2sleep * 1000);
}
