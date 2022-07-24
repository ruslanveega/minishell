/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:03:29 by cdell             #+#    #+#             */
/*   Updated: 2022/07/24 01:19:34 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*get_token_value(int token_key, char *start, const char *end)
{
	char	*tmp;
	int		size;
	char	*token_value;

	if (token_key == SINGLE_QUOTE || token_key == DOUBLE_QUOTE
		|| token_key == ENV_VAR)
		start++;
	tmp = start;
	size = 0;
	while (*tmp && tmp < end)
	{
		tmp++;
		size++;
	}
	if (token_key != SINGLE_QUOTE && token_key != DOUBLE_QUOTE)
		size++;
	token_value = (char *)malloc(sizeof(char) * size);
	if (!token_value)
		ft_puterror("Failed to allocate memory");
	ft_strlcpy(token_value, start, size);
	return (token_value);
}

static int	get_token_key(char **line, char **tk_start, char **tk_end)
{
	char	*str;
	int		token;

	str = *line;
	if (tk_start)
		*tk_start = str;
	if (*str == '|' || *str == '(' || *str == ')')
	{
		token = (int) *str;
		str++;
	}
	else if (*str == '<' || *str == '>')
		token = get_redirect_token(&str);
	else if (ft_strchr(WHITE_SPACE_CHARS, *str))
		token = get_space_token(&str);
	else if (*str == '\'' || *str == '"')
		token = get_quote_tk(&str, *str);
	else
		token = get_word_token(&str);
	if (tk_end)
		*tk_end = str;
	*line = str;
	return (token);
}

void	build_token_list(char **line, t_sl_list **token_list)
{
	size_t	token_key;
	char	*token_value;
	char	*t_start;
	char	*t_end;

	while (**line)
	{
		token_key = get_token_key(line, &t_start, &t_end);
		if (token_key != WORD && token_key != ENV_VAR
			&& token_key != DOUBLE_QUOTE && token_key != SINGLE_QUOTE)
			token_value = NULL;
		else
			token_value = get_token_value(token_key, t_start, t_end);
		lst_append_node(token_list, (void *)token_key, (void *)token_value);
//		lst_append_node(token_list, (void *)token_key, (void *)token_value);
	}
}

t_sl_list	*get_token_list(char *tmp)
{
	t_sl_list	*token_list;
	char		*line;
	// char		*tmp;

	// tmp = readline("");
	line = ft_strtrim(tmp, WHITE_SPACE_CHARS);
	// free (tmp);
	if (!line)
		ft_puterror("Failed to allocate memory *get_token_list(void)");
	tmp = line;
	build_token_list(&line, &token_list);
	print_list(token_list);
	free(tmp);
	return (token_list);
}

