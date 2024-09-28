/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shonakam <shonakam@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 03:47:28 by shonakam          #+#    #+#             */
/*   Updated: 2024/09/26 14:48:00 by shonakam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <limits.h>
# include <unistd.h>

int			ft_atoi(const char *s);
long long	ft_atoll(const char *s);

int			ft_is_digit(char c);
int			ft_is_plus_minus(char c);
int			ft_is_whitespace(char c);
char		*ft_skipwhitespace(char *s);
size_t		ft_putchar_fd(int c, int fd);
size_t		ft_putstr_fd(char *str, int fd);
