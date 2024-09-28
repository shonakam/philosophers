/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:55:15 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/25 15:57:49 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/utils.h"

char	*ft_skipwhitespace(char *s)
{
	while (ft_is_whitespace(*s))
		s++;
	return (s);
}