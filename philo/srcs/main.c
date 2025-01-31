/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 00:26:50 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 04:37:56 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	ft_usage(char *name)
{
	ft_putstr_fd("Usage: ", STDERR_FILENO);
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(" number_of_philosophers", STDERR_FILENO);
	ft_putstr_fd(" time_to_die time_to_eat time_to_sleep ", STDERR_FILENO);
	ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n", 2);
}
/* param shuld be only number.  */
static int	validator(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_is_whitespace(av[i][j]))
				if (!ft_is_digit(av[i][j]))
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_simulation	sim;

	if (ac < 5 || 6 < ac)
		return (ft_usage(av[0]), EXIT_FAILURE);
	if (validator(av))
		return (EXIT_FAILURE);
	if (ft_philo_init(&sim, av))
		return (EXIT_FAILURE);
	if (start_simulation(&sim, sim.num_philo))
		return (EXIT_FAILURE);
	cleanup(&sim);
}
// printf("\033[31mBREAKPOINT\033[0m\n");

// __attribute__((destructor))
// static void destructor() {
// 	system("leaks -q philo");
// }
