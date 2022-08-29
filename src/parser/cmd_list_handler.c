/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 14:32:17 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 02:22:23 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cmd_list	*get_new_cmd(t_redir *redirect, char *cmd_options[])
{
	t_cmd_list	*cmd;

	cmd = (t_cmd_list *)malloc(sizeof(t_cmd_list));
	if (!cmd)
		init_err(MEM_ERR, "", 1, 0);
	cmd->cmd_options = cmd_options;
	cmd->redirect = redirect;
	cmd->next = NULL;
	return (cmd);
}

static t_cmd_list	*lst_get_last_node(t_cmd_list *list)
{
	if (!list)
		return (NULL);
	while (list->next)
		list = list->next;
	return (list);
}

static void	lst_add_back_node(t_cmd_list **list, t_cmd_list *new_node)
{
	t_cmd_list	*last;

	if (!new_node)
		return ;
	if (*list)
	{
		last = lst_get_last_node(*list);
		last->next = new_node;
	}
	else
		*list = new_node;
}

// void	clear_cmd_list(t_cmd_list **list)
// {
// 	t_cmd_list	*tmp;

// 	if (!*list)
// 		return ;
// 	while (*list)
// 	{
// 		tmp = *list;
// 		*list = (*list)->next;
// 		ft_lstclear(&tmp->redirect, clear_token);
// 		clear_array(tmp->cmd_options);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	list = NULL;
// }

void	append_cmd(t_cmd_list **cmd_list, t_redir *redirect, char *cmd_options[])
{
	t_cmd_list	*cmd;

	cmd = get_new_cmd(redirect, cmd_options);
	lst_add_back_node(cmd_list, cmd);
}
