/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_token_ops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 18:20:27 by cdell             #+#    #+#             */
/*   Updated: 2022/06/14 22:43:55 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*lst_last_token(t_token *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->next)
		token_list = token_list->next;
	return (token_list);
}

t_token	*lst_new_token(int key, void *value)
{
	t_token	*token;

	token = (t_token *) malloc(sizeof (t_token));
	if (!token)
		ft_puterror("Failed to allocate memory for token");
	token->key = key;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	lst_add_back_token(t_token **token_list, t_token *new_token)
{
	t_token	*last;

	if (!*token_list && !new_token)
		return ;
	if (*token_list)
	{
		last = lst_last_token(*token_list);
		last->next = new_token;
	}
	else
		*token_list = new_token;
}

void	lst_add_token(t_token **token_list, int key, void *value)
{
	t_token	*token;

	token = lst_new_token(key, value);
	lst_add_back_token(token_list, token);
}

void	lst_clear(t_token **token_lst)
{
	t_token	*tmp;

	if (!*token_lst)
		return ;
	while (*token_lst)
	{
		tmp = *token_lst;
		*token_lst = (*token_lst)->next;
		free(tmp->value);
		free((tmp));
	}
}
