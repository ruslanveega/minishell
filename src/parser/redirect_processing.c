/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:39:22 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 00:48:35 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// static t_redirect	*create_new_redirect(int type, char *file)
// {
// 	t_redirect	*node;

// 	node = NULL;
// 	node = (t_redirect *)malloc(sizeof (t_redirect));
// 	if (!node)
// 		ft_puterror("Failed to allocate memory for redirect in\
// 		 redirect_processing.c->create_new_redirect");
// 	node->type = type;
// 	node->file = file;
// 	return (node);
// }

// void	append_redirect(t_list **redirect_list, int type, char *value)
// {
// 	t_redirect	*redirect;
// 	t_list		*new_node;

// 	redirect = create_new_redirect(type, value);
// 	new_node = ft_lstnew((void *)redirect);
// 	if (!new_node)
// 		ft_puterror("Could not allocate memory in parser.c->get_cmd_list");
// 	ft_lstadd_back(redirect_list, new_node);
// }

void	add_redirect_node(t_list *token_list, t_redir *redirect_list)
{
	t_redir	*redirect_list;
	t_token	*token;

	while (redirect_list->next)
		redirect_list = redirect_list->next;

	redirect_list->next = malloc(sizeof(t_redir));
	if (!redirect_list->next)
		init_err(MEM_ERR, "", 1, 0);
	redirect_list->type = get_token_node_key(token_list);
	token = (t_token *)token_list->next->content;
	redirect_list->file = ft_strdup(token->value);
	if (!redirect_list->file)
		init_err(MEM_ERR, "", 1, 0);
	redirect_list->next = NULL;
}
