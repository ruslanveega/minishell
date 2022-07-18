/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 23:19:50 by cdell             #+#    #+#             */
/*   Updated: 2021/10/26 19:25:34 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word_count(char const *s, char c)
{
	int	word_count;
	int	i;

	word_count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] != c && s[i])
				i++;
			word_count++;
		}
		else
			i++;
	}
	return (word_count);
}

static int	ft_word_length(char const *s, char c)
{
	int	n;

	n = 0;
	while (s[n] != c && s[n])
		n++;
	return (n);
}

static void	*ft_clean(char **word_array, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(word_array[i++]);
	free(word_array);
	return ((void *) 0);
}

char	**ft_split(char const *s, char c)
{
	char	**word_array;
	int		i;
	int		j;

	if (!s)
		return ((void *) 0);
	word_array = (char **)ft_calloc(sizeof(char *), (ft_word_count(s, c) + 1));
	if (word_array == (void *)0)
		return ((void *)0);
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			word_array[j] = ft_substr(s, i, ft_word_length(s + i, c));
			if (word_array[j++] == (void *) 0)
				return (ft_clean(word_array, j));
			i += ft_word_length(s + i, c);
		}
		else
			i++;
	}
	return (word_array);
}
