/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 00:56:44 by cdell             #+#    #+#             */
/*   Updated: 2021/10/22 01:30:32 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;
	int					i;

	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	if (!dst && ! src)
		return ((void *) 0);
	if (dst_ptr > src_ptr && dst_ptr < (src_ptr + len))
	{
		i = len - 1;
		while (i >= 0)
		{
			dst_ptr[i] = src_ptr[i];
			i--;
		}
		return (dst);
	}
	i = 0;
	while (i < (int)len)
	{
		dst_ptr[i] = src_ptr[i];
		i++;
	}
	return (dst);
}
