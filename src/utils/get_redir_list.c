/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:44:37 by cdell             #+#    #+#             */
/*   Updated: 2022/08/31 21:32:48 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_redir	*create_new_node(t_redirect *redirect)
{
	t_redir	*node;

	node = (t_redir *)malloc(sizeof(t_redir));
	if (!node)
		init_err(MEM_ERR, "", 1, 12);
	node->type = redirect->type;
	node->file = ft_strdup(redirect->file);
	node->next = NULL;
	return (node);
}

static t_redir	*get_last_node(t_redir *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static void	add_back_node(t_redir **list, t_redir *new_node)
{
	t_redir	*last;

	if (!new_node)
		return ;
	if (*list)
	{
		last = get_last_node(*list);
		last->next = new_node;
	}
	else
		*list = new_node;
}

static void	append_redir_node(t_redir **list, t_redirect *node)
{
	t_redir	*redirect;

	redirect = create_new_node(node);
	add_back_node(list, redirect);
}

t_redir	*get_redir_list(t_list *redirect_list)
{
	t_redir		*redir_list;
	t_redirect	*node;

	redir_list = (t_redir *)malloc(sizeof(t_redir));
	if (!redir_list)
		init_err(MEM_ERR, "", 1, 12);
	while (redirect_list)
	{
		node = (t_redirect *)redirect_list->content;
		append_redir_node(&redir_list, node);
		redirect_list = redirect_list->next;
	}
	return (redir_list);
}
