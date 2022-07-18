/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 01:05:40 by cdell             #+#    #+#             */
/*   Updated: 2021/10/23 06:22:04 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trimmed;
	int		i;
	int		j;

	if (s1 == (void *)0)
		return ((void *)0);
	if (set == (void *)0 || ft_strlen(set) == 0)
		return (ft_strdup(s1));
	i = 0;
	j = ft_strlen(s1) - 1;
	while (s1[i] && (ft_strchr(set, s1[i]) != NULL))
		i++;
	if (s1[i] == '\0')
		return (ft_strdup(""));
	while (j > 0 && ft_strchr(set, s1[j]) != NULL)
		j--;
	str_trimmed = ft_substr(s1, i, (j - i) + 1);
	return (str_trimmed);
}
