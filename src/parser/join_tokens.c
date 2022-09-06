/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:04:20 by cdell             #+#    #+#             */
/*   Updated: 2022/09/03 21:02:43 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	should_join(int key)
{
	if (key == WORD || key == SINGLE_QUOTE || key == DOUBLE_QUOTE
		|| key == ENV_VAR || key == EXIT_STATUS)
		return (1);
	return (0);
}

//int	should_join(size_t key)
//{
//	if (key == WORD)
//		return (1);
//	return (0);
//}

static void	*join_strs(void *current, void *next)
{
	t_token	*t1;
	t_token	*t2;
	char	*joined_str;

	t1 = (t_token *)current;
	t2 = (t_token *)next;
	joined_str = ft_strjoin(t1->value, t2->value, NULL);
	return (joined_str);
}

static void	join_tokens(t_list *token_list)
{
	t_list	*tmp;
	t_token	*token;
	char	*joined_str;

	tmp = token_list->next;
	if (token_list->content)
	{
		if (tmp->content)
		{
			joined_str = join_strs(token_list->content, tmp->content);
			token = token_list->content;
			free(token->value);
			token->value = joined_str;
		}
		token_list->next = tmp->next;
		clear_token(tmp->content);
		free(tmp);
	}
}

void	join_token_list(t_list *token_list)
{
	t_token	*token;
	t_token	*next;

	while (token_list)
	{
		token = token_list->content;
		if (token_list->next)
			next = token_list->next->content;
		if (should_join(token->key)
			&& (next && should_join(next->key)))
			join_tokens(token_list);
		else
			token_list = token_list->next;
		token = NULL;
		next = NULL;
	}
}
