/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:32:46 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 03:22:17 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

int	ft_atoi(const char *s)
{
	return ((int)ft_atoll(s));
}

// #include <stdio.h>
// #include <stdlib.h>
// int main(int ac, char **av)
// {
//     if (ac != 2)
//     {
//         printf("Usage: %s <number_string>\n", av[0]);
//         return 1;
//     }

//     const char *num_str = av[1];

//     // ft_atoi と標準 atoi の比較
//     printf("String '%s' converted to long: %ld\n", num_str, ft_atol(num_str));
//     printf("String '%s' converted to int (ft_atoi): %d\n", num_str, ft_atoi(num_str));
//     printf("String '%s' converted to int (atoi): %d\n", num_str, atoi(num_str));

//     return 0;
// }