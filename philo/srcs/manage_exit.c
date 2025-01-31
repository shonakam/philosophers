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
	{
		free(sim->forks);
		sim->forks = NULL;
	}
	if (sim->philosophers)
	{
		free(sim->philosophers);
		sim->philosophers = NULL;
	}
	if (sim->threads)
	{
		free(sim->threads);
		sim->threads = NULL;
	}
}

void	cleanup(t_simulation *sim, int f)
{
	int	i;

	// スレッドの終了を待つ
	if (sim->threads)
	{
		for (i = 0; i < sim->num_philo; i++)
			pthread_join(sim->threads[i], NULL);
		pthread_join(sim->threads[sim->num_philo], NULL); // モニタースレッド
	}

	// ミューテックスの解放
	if (f && sim->philosophers)
	{
		for (i = 0; i < sim->num_philo; i++)
		{
			pthread_mutex_destroy(&sim->forks[i]);
			pthread_mutex_destroy(&sim->philosophers[i].starvation_mtx);
			pthread_mutex_destroy(&sim->philosophers[i].times_eaten_mtx);
			pthread_mutex_destroy(&sim->philosophers[i].dead_mtx);
			pthread_mutex_destroy(&sim->philosophers[i].fin_mtx);
		}
	}

	// シミュレーション全体のミューテックス解放
	pthread_mutex_destroy(&sim->diedlog_mtx);
	pthread_mutex_destroy(&sim->stop_mtx);

	// メモリの解放
	free_all(sim);
}
