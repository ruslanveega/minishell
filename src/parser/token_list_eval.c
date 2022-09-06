/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_eval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:13:42 by cdell             #+#    #+#             */
/*   Updated: 2022/09/03 21:04:23 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*get_error_msg(int key)
{
	if (key == 0)
		return (NEWLINE_STR);
	else if (key == REDIRECT_IN)
		return (REDIRECT_IN_STR);
	else if (key == REDIRECT_OUT)
		return (REDIRECT_OUT_STR);
	else if (key == REDIRECT_APPEND)
		return (REDIRECT_APPEND_STR);
	else if (key == REDIRECT_HEREDOC)
		return (REDIRECT_HEREDOC_STR);
	else if (key == PIPE)
		return (PIPE_STR);
	return (NULL);
}

static int	evaluate_redirect(t_list *token_list)
{
	while (token_list)
	{
		if (is_redirect(get_token_node_key(token_list)))
		{
			if (!token_list->next)
			{
				init_err(SYN_ERR, NEWLINE_STR, 0, 258);
				return (ERROR);
			}
			if (get_token_node_key(token_list->next) != WORD)
			{
				init_err(SYN_ERR, get_error_msg(
						get_token_node_key(token_list->next)), 0, 258);
				return (ERROR);
			}
		}
		token_list = token_list->next;
	}
	return (SUCCESS);
}

static int	evaluate_pipes(t_list *token_list)
{
	if (get_token_node_key(token_list) == PIPE)
	{
		init_err(SYN_ERR, PIPE_STR, 0, 258);
		return (ERROR);
	}
	while (token_list->next)
	{
		if (get_token_node_key(token_list) == PIPE
			&& get_token_node_key(token_list->next) == PIPE)
		{
			init_err(SYN_ERR, PIPE_STR, 0, 258);
			return (ERROR);
		}
		token_list = token_list->next;
	}
	if (get_token_node_key(token_list) == PIPE)
	{
		init_err(SYN_ERR, PIPE_STR, 0, 258);
		return (ERROR);
	}
	return (SUCCESS);
}

int	evaluate_token_list(t_list *token_list)
{
	if (!evaluate_pipes(token_list) || !evaluate_redirect(token_list))
		return (ERROR);
	return (SUCCESS);
}
