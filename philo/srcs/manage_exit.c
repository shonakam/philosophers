#include "includes/philo.h"

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

static void destory_philo_mtx(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->num_philo)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		pthread_mutex_destroy(&sim->philosophers[i].starvation_mtx);
		pthread_mutex_destroy(&sim->philosophers[i].times_eaten_mtx);
		pthread_mutex_destroy(&sim->philosophers[i].dead_mtx);
		pthread_mutex_destroy(&sim->philosophers[i].fin_mtx);
		i++;
	}
}

void	cleanup(t_simulation *sim, int f)
{
	int	i;

	if (!sim)
		return ;
	if (sim->threads)
	{
		i = 0;
		while (i < sim->num_philo)
		{
			if (sim->threads[i])
				pthread_join(sim->threads[i], NULL);
			i++;
		}
		if (sim->threads[sim->num_philo])
			pthread_join(sim->threads[sim->num_philo], NULL);
	}
	if (f && sim->philosophers)
		destory_philo_mtx(sim);
	pthread_mutex_destroy(&sim->diedlog_mtx);
	pthread_mutex_destroy(&sim->stop_mtx);
	pthread_mutex_destroy(&sim->monitor_mtx);
	free_all(sim);
}
