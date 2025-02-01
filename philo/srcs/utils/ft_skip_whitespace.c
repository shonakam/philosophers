/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_whitespace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:55:15 by shonakam          #+#    #+#             */
/*   Updated: 2025/02/01 13:11:11 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils.h"

char	*ft_skipwhitespace(char *s)
{
	while (ft_is_whitespace(*s))
		s++;
	return (s);
}