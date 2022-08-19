/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:39:22 by cdell             #+#    #+#             */
/*   Updated: 2022/08/11 06:39:26 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//static char	*get_redirect_value(t_list *token_list)
//{
//	t_token	*token;
//	char	*file;
//
//	token = (t_token *)token_list->next->content;
//	file = ft_strdup(token->value);
//	if (!file)
//		ft_puterror("Failed to allocate memory for redirection in [redirect_processing.c->process_redirect]");
//	return (file);
//}

static t_redirect	*create_new_redirect(int type, char *file)
{
	t_redirect	*node;

	node = NULL;
	node = (t_redirect *)malloc(sizeof (t_redirect));
	if (!node)
		ft_puterror("Failed to allocate memory for redirect in redirect_processing.c->create_new_redirect");
	node->type = type;
	node->file = file;
	return (node);
}

//t_redirect *get_redirect(t_list *token_list)
//{
//	t_redirect	*redirect;
//	char		*file;
//
//	redirect = (t_redirect *)malloc(sizeof(t_redirect));
//	if (!redirect)
//		ft_puterror("Failed to allocate memory for redirection in [redirect_processing.c->process_redirect]");
//	redirect->type = get_token_key(token_list);
//	file = get_redirect_value(token_list);
//	redirect->file = file;
//	return (redirect);
//}

void append_redirect(t_list **redirect_list, int type, char *value)
{
	t_redirect *redirect;
	t_list *new_node;

	redirect = create_new_redirect(type, value);
	new_node = ft_lstnew((void *)redirect);
	if (!new_node)
		ft_puterror("Could not allocate memory in parser.c->get_cmd_list");
	ft_lstadd_back(redirect_list, new_node);
}
