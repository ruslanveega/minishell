/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 01:00:40 by cdell             #+#    #+#             */
/*   Updated: 2021/10/23 05:47:20 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	size_t	s1_length;
	size_t	s2_length;

	if (s1 == (void *)0 || s2 == (void *)0)
		return ((void *) 0);
	s1_length = ft_strlen(s1);
	s2_length = ft_strlen(s2);
	new_str = malloc(sizeof(char) * s1_length + s2_length + 1);
	if (new_str == (void *) 0)
		return ((void *) 0);
	ft_strlcpy(new_str, s1, s1_length + 1);
	ft_strlcat(new_str, s2, s1_length + s2_length + 1);
	return (new_str);
}
