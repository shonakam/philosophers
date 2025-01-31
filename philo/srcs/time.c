/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 17:26:30 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 02:32:46 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (long long)1000) + (tv.tv_usec / (long long)1000));
}

static long long get_elapsed_time_ms(struct timeval start, struct timeval end)
{
	long long	r;

	r = (end.tv_sec - start.tv_sec) * 1000000LL;
	r += end.tv_usec - start.tv_usec;
	return (r);
}

/* https://ja.manpages.org/usleep/3 */
void	wraped_sleep(long long time)
{
	struct timeval	start;
	struct timeval	current;
	long long		elapsed;
	long long		rem;

	elapsed = 0;
	gettimeofday(&start, NULL);
	while (elapsed < time)
	{
		gettimeofday(&current, NULL);
		elapsed = get_elapsed_time_ms(start, current);
		rem = time - elapsed;
		if (rem > 1000)
			usleep(rem / 2);
	}
}


