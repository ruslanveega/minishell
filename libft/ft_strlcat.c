/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 01:01:11 by cdell             #+#    #+#             */
/*   Updated: 2021/10/22 03:10:22 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_length;
	size_t	src_length;
	size_t	i;

	dst_length = ft_strlen(dst);
	src_length = ft_strlen(src);
	i = 0;
	if (dstsize == 0 || (dstsize - 1 < dst_length))
		return (dstsize + src_length);
	if (dstsize - 1 > dst_length)
	{
		while (src[i] != '\0' && (dst_length + i) < (dstsize - 1))
		{
			dst[dst_length + i] = src[i];
			i++;
		}
		dst[dst_length + i] = '\0';
	}
	return (dst_length + src_length);
}
