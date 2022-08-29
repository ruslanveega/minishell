/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:33:29 by cdell             #+#    #+#             */
/*   Updated: 2022/08/29 04:21:28 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "parser.h"

// void	print_options(char *str[])
// {
// 	int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		printf("command = %s\n", str[i]);
// 		i++;
// 	}
// }

// static void	print_node(t_redirect *node)
// {
// 	if (node->type == REDIRECT_IN)
// 		printf("redirect type = <\t");
// 	else if (node->type == REDIRECT_OUT)
// 		printf("redirect type = >\t");
// 	else if (node->type == REDIRECT_APPEND)
// 		printf("redirect type = >>\t");
// 	else if (node->type == REDIRECT_HEREDOC)
// 		printf("redirect type = <<\t");
// 	printf("file = %s\n", node->file);
// }

// void	print_redirect_list(t_list *list)
// {
// 	t_redirect	*node;

// 	while (list)
// 	{
// 		node = (t_redirect *)list->content;
// 		print_node(node);
// 		list = list->next;
// 	}
// }

// void	print_cmd_list(t_cmd_list *cmd_list)
// {
// 	if (!cmd_list)
// 		printf("not cmd_list\n");
// 	while (cmd_list)
// 	{
// 		print_options(cmd_list->cmd_options);
// 		print_redirect_list(cmd_list->redirect);
// 		cmd_list = cmd_list->next;
// 	}
// }
