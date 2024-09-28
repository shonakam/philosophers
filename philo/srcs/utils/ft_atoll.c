/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:53:27 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/26 06:58:32 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/utils.h"

long long	ft_atoll(const char *s)
{
	long long	r;
	long long	sign;

	r = 0; 
	sign = 1;
	while (ft_is_whitespace((char)*s))
		s++;
	if (ft_is_plus_minus((char)*s))
		if (*s++ == '-')
			sign = -1;
	while (ft_is_digit((char)*s))
	{
		if (r > (LLONG_MAX - (*s - '0')) / 10)
		{
			if (sign == 1)
				return (LLONG_MAX);
			else
				return (LLONG_MIN);
		}
		r = r * 10 + (*s++ - 48);
	}
	return (r * sign);
}
