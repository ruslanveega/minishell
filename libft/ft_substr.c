/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 01:06:13 by cdell             #+#    #+#             */
/*   Updated: 2021/10/21 04:03:35 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr_ptr;
	size_t	substr_len;

	if (s == (void *) 0)
		return ((void *) 0);
	if (ft_strlen(s) <= start)
		substr_len = 0;
	else if (ft_strlen(s) < start + len)
		substr_len = ft_strlen(s + start);
	else
		substr_len = len;
	substr_ptr = malloc(sizeof(char) * substr_len + 1);
	if (substr_ptr == (void *)0)
		return ((void *)0);
	ft_strlcpy(substr_ptr, s + start, substr_len + 1);
	return (substr_ptr);
}
