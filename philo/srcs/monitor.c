/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:56:18 by shonakam          #+#    #+#             */
/*   Updated: 2025/01/31 22:23:10 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

static void mtx_all(t_simulation *sim, int f)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		if (f)
		{
			pthread_mutex_lock(&sim->philosophers[i].starvation_mtx);
			pthread_mutex_lock(&sim->philosophers[i].dead_mtx);
		}
		else
		{
			pthread_mutex_unlock(&sim->philosophers[i].starvation_mtx);
			pthread_mutex_unlock(&sim->philosophers[i].dead_mtx);
		}
		i++;
	}
}

/**
 * 各哲学者が餓死していないかをチェック
 * 餓死していた場合、その哲学者の `is_dead` を設定し、ログを出力する。
 */
static void check_starvation(t_simulation *sim)
{
	int i = 0;
	while (i < sim->num_philo)
	{
		pthread_mutex_lock(&sim->philosophers[i].starvation_mtx);
		if (get_time() > sim->philosophers[i].to_starvation)
		{
			pthread_mutex_lock(&sim->philosophers[i].dead_mtx);
			sim->philosophers[i].is_dead = 1;
			pthread_mutex_unlock(&sim->philosophers[i].dead_mtx);
			
			log_action(&sim->philosophers[i], sim->philosophers[i].id, "\033[31mdied\033[0m");

			pthread_mutex_lock(&sim->stop_mtx);
			sim->is_stop = 1;
			pthread_mutex_unlock(&sim->stop_mtx);
			pthread_mutex_unlock(&sim->philosophers[i].starvation_mtx);
			return;
		}
		pthread_mutex_unlock(&sim->philosophers[i].starvation_mtx);
		i++;
	}
}

/**
 * 哲学者の死亡をチェックし、シミュレーションを停止する
 */
static int check_death(t_simulation *sim)
{
	int i;
	int dead;

	mtx_all(sim, 1);  // 🔹 すべてのロックを取得
	i = 0;
	while (i < sim->num_philo)
	{
		// pthread_mutex_lock(&sim->lock);
		pthread_mutex_lock(&sim->philosophers[i].dead_mtx);
		dead = sim->philosophers[i].is_dead;
		pthread_mutex_unlock(&sim->philosophers[i].dead_mtx);

		if (dead)
		{
			pthread_mutex_lock(&sim->stop_mtx);
			sim->is_stop = 1;
			pthread_mutex_unlock(&sim->stop_mtx);
			mtx_all(sim, 0);
			return (1);
		}
		i++;
		// pthread_mutex_unlock(&sim->lock);
	}
	mtx_all(sim, 0);
	return (0);
}

/**
 * すべての哲学者が食事を終えたかをチェックし、シミュレーションを停止する
 */
static int check_all_finished(t_simulation *sim)
{
	int i = 0;
	int finished_count = 0;

	while (i < sim->num_philo)
	{
		pthread_mutex_lock(&sim->philosophers[i].fin_mtx);
		if (sim->philosophers[i].is_fin)
			finished_count++;
		pthread_mutex_unlock(&sim->philosophers[i].fin_mtx);
		i++;
	}

	mtx_all(sim, 1);
	if (finished_count == sim->num_philo)
	{
		pthread_mutex_lock(&sim->stop_mtx);
		sim->is_stop = 1;
		mtx_all(sim, 0);
		pthread_mutex_unlock(&sim->stop_mtx);
		return (1);
	}
	mtx_all(sim, 0);
	return (0);
}

/**
 * 監視スレッド（`monitor`）
 * - `check_starvation()`
 * - `check_death()`
 * - `check_all_finished()`
 * を呼び出してシミュレーションの状態を監視する。
 */
void	*monitor(void *arg)
{
	t_simulation *sim = (t_simulation *)arg;

	while (1)
	{
		check_starvation(sim);
		if (check_death(sim) || check_all_finished(sim))
		{
			return (NULL);
		}
		wraped_sleep(10000);
	}
	return (NULL);
}
