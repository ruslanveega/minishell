/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:37:30 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 16:18:13 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static t_token	*create_new_token(int key, char *value)
{
	t_token	*node;

	node = NULL;
	node = (t_token *)malloc(sizeof(t_token));
	if (!node)
		ft_puterror("Failed to allocate memory for token");
	node->key = key;
	node->value = value;
	return (node);
}

void	clear_token(void *token)
{
	t_token	*t;

	t = (t_token *)token;
	free(t->value);
	free(t);
	t = NULL;
}

void	append_token(t_list **token_list, int key, char *value)
{
	t_token	*token;
	t_list	*new_node;

	token = create_new_token(key, value);
	new_node = ft_lstnew((void *)token);
	ft_lstadd_back(token_list, new_node);
}
