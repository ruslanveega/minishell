/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_value_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 06:44:32 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 16:21:46 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

char	*get_env_var_value(char *start, const char *end)
{
	char	*str;

	start++;
	str = get_word_value(start, end);
	return (str);
}

char	*get_word_value(char *start, const char *end)
{
	char	*str;
	size_t	length;

	if (*start == '$' && ft_isdigit(*(start + 1)))
		start += 2;
	length = ft_substr_len(start, end);
	if (length == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * length + 1);
	ft_strlcpy(str, start, length + 1);
	return (str);
}

static int	get_status(void)
{
	return (0);
}

char	*get_exit_status(void)
{
	char	*str;

	str = ft_itoa(get_status());
	return (str);
}

char	*get_quotes_value(char *start, int type)
{
	char	*str;
	size_t	length;

	start++;
	length = 0;
	str = start;
	while (*str && *str != type)
	{
		length++;
		str++;
	}
	if (length == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * length + 1);
	ft_strlcpy(str, start, length + 1);
	return (str);
}
