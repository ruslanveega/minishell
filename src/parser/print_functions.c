/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:33:29 by cdell             #+#    #+#             */
/*   Updated: 2022/08/16 22:33:32 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void print_options(char *str[])
{
	int i = 0;

	while (str[i])
	{
		printf("command = %s\n", str[i]);
		i++;
	}
}

static void print_node(t_redirect *node)
{
	if (node->type == REDIRECT_IN)
		printf("redirect type = <\t");
	else if (node->type == REDIRECT_OUT)
		printf("redirect type = >\t");
	else if (node->type == REDIRECT_APPEND)
		printf("redirect type = >>\t");
	else if (node->type == REDIRECT_HEREDOC)
		printf("redirect type = <<\t");
	printf("file = %s\n", node->file);
}

void print_redirect_list(t_list *list)
{
	t_redirect *node;

//	if (!list)
//	{
//		printf("redirect_list var list is empty\n");
//		exit(EXIT_FAILURE);
//	}
	while (list)
	{
		node = (t_redirect *)list->content;
		print_node(node);
		list = list->next;
	}
}

void print_cmd_list(t_cmd_list *cmd_list)
{
	if (!cmd_list)
		printf("not cmd_list\n");
	while (cmd_list)
	{
		print_options(cmd_list->cmd_options);
		print_redirect_list(cmd_list->redirect);
		cmd_list = cmd_list->next;
	}
}