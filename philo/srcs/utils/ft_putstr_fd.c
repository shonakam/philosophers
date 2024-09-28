/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:35:35 by kmoshker          #+#    #+#             */
/*   Updated: 2024/09/26 07:04:08 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/utils.h"

size_t	ft_putstr_fd(char *str, int fd)
{
	size_t	i;

	i = 0;
	if (!str)
		return (ft_putstr_fd("(null)", 1));
	while (str[i])
	{
		ft_putchar_fd(str[i], fd);
		i++;
	}
	return (i);
}
