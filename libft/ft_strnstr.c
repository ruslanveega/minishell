/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 01:04:41 by cdell             #+#    #+#             */
/*   Updated: 2021/10/23 05:22:15 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	needle_length;

	i = 0;
	needle_length = ft_strlen(needle);
	if (needle_length == 0)
		return ((char *)haystack);
	while (haystack[i] && i < len)
	{
		while (haystack[i] != needle[0] && (haystack[i] != '\0' && i < len))
			i++;
		if (haystack[i] == '\0' || needle_length + i > len)
			break ;
		if (ft_strncmp(haystack + i, needle, needle_length) == 0)
			return ((char *)haystack + i);
		i++;
	}
	return ((void *)0);
}
