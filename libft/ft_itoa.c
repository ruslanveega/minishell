/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 00:53:15 by cdell             #+#    #+#             */
/*   Updated: 2021/10/26 19:25:06 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_length(int n)
{
	int	length;

	if (n == 0)
		length = 1;
	else
	{
		if (n < 0)
			length = 1;
		else
			length = 0;
		while (n != 0)
		{
			n /= 10;
			length ++;
		}
	}
	return (length);
}

static void	ft_get_number(char *s, long n, int index)
{
	if (n < 10)
		s[index] = n + '0';
	else
	{
		ft_get_number(s, n / 10, --index);
		s[++index] = n % 10 + '0';
	}
}

char	*ft_itoa(int n)
{
	char	*str;
	long	num;
	int		length;

	num = n;
	length = ft_get_length(n);
	str = (char *)malloc(sizeof(char) * length + 1);
	if (str == (void *) 0)
		return ((void *) 0);
	if (num < 0)
	{
		num *= -1;
		str[0] = '-';
	}
	ft_get_number(str, num, length - 1);
	str[length] = '\0';
	return (str);
}
