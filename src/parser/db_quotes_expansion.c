/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_quotes_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 06:36:23 by cdell             #+#    #+#             */
/*   Updated: 2022/09/06 04:17:45 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	get_sum_of_lens(t_list *list)
{
	t_str_chunk	*chunk;
	size_t		length;

	length = 0;
	while (list)
	{
		chunk = list->content;
		length += chunk->length;
		list = list->next;
	}
	return (length);
}

static void	handle_env_var_chunk(t_list **db_quote_chunk, char **str)
{
	char	*start;
	char	*end;
	size_t	length;
	char	*chunk;

	chunk = NULL;
	(*str)++;
	start = *str;
	while (**str && (ft_isalnum(**str) || **str == '_'))
		(*str)++;
	end = *str;
	chunk = lookup_env_var_val(start, end);
	if (chunk)
	{
		length = ft_strlen(chunk);
		append_chunk(db_quote_chunk, length, chunk);
	}
}

static void	handle_str_chunk(t_list **db_quote_chunk, char **str)
{
	char	*start;
	char	*end;
	size_t	length;
	char	*chunk;

	chunk = NULL;
	if (**str == '$' && ft_isdigit(*((*str) + 1)))
		(*str) += 2;
	start = *str;
	while (**str)
	{
		if (**str == '$' && ft_isalnum(*((*str) + 1)))
			break ;
		(*str)++;
	}
	end = *str;
	length = ft_substr_len(start, end);
	chunk = (char *)malloc(sizeof(char) * length + 1);
	if (!chunk)
		init_err(MEM_ERR, "", 1, 0);
	ft_strlcpy(chunk, start, length + 1);
	append_chunk(db_quote_chunk, length, chunk);
}

static t_list	*build_chunk_list(char *db_quote_str)
{
	t_list	*str_chunk_lst;
	char	*str;

	str_chunk_lst = NULL;
	str = db_quote_str;
	while (*str)
	{
		if (*str == '$' && !ft_isdigit(*(str + 1)))
		{
			if (ft_isalpha(*(str + 1)))
				handle_env_var_chunk(&str_chunk_lst, &str);
			else if (*(str + 1) == '?')
				handle_exit_status(&str_chunk_lst, &str);
		}
		else
			handle_str_chunk(&str_chunk_lst, &str);
	}
	return (str_chunk_lst);
}

char	*get_str_from_db_quotes(char *db_quotes_str)
{
	t_list		*str_chunk_lst;
	t_str_chunk	*chunk;
	t_list		*tmp;
	char		*str;
	size_t		str_len;

	str_chunk_lst = build_chunk_list(db_quotes_str);
	if (!str_chunk_lst)
		return (NULL);
	str_len = get_sum_of_lens(str_chunk_lst);
	str = (char *) malloc(sizeof(char) * str_len + 1);
	if (!str)
		init_err(MEM_ERR, "", 1, 0);
	tmp = str_chunk_lst;
	str_len = 0;
	while (tmp)
	{
		chunk = tmp->content;
		ft_strlcpy(str + str_len, chunk->str, chunk->length + 1);
		str_len += chunk->length;
		tmp = tmp->next;
	}
	ft_lstclear(&str_chunk_lst, clear_str_chunk);
	return (str);
}
