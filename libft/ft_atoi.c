/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 00:50:15 by cdell             #+#    #+#             */
/*   Updated: 2021/10/26 19:24:52 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if ((c == '\t' || c == '\n' || c == '\v')
		|| (c == '\f' || c == '\r' || c == ' '))
		return (1);
	return (0);
}

static int	ft_isoverflow(unsigned long long n, int sign)
{
	if (n > 9223372036854775807U && sign > 0)
		return (-1);
	else if (n > 9223372036854775808U && sign < 0)
		return (0);
	else
		return ((int)n * sign);
}

int	ft_atoi(const char *str)
{
	unsigned long long	n;
	int					sign;

	n = 0;
	sign = 1;
	if (*str == '\0')
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n = (n * 10) + *str - '0';
		str++;
	}
	n = ft_isoverflow(n, sign);
	return (n);
}
