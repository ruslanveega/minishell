/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Abdu-Rashid <Abdu-Rashid@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:44:37 by cdell             #+#    #+#             */
/*   Updated: 2022/07/30 23:20:05 by Abdu-Rashid      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	process_token_list(t_list *token_list)
{
	t_list	*tokens;

	tokens = token_list;
	expand_token_list(tokens);
	join_token_list(tokens);
	strip_space(tokens);
	evaluate_token_list(tokens);
}

t_cmd_list	*parse_input(char *line)
{
	t_cmd_list	*cmd_list;
	t_list		*token_list;

	cmd_list = NULL;
	token_list = get_token_list(line);
	process_token_list(token_list);
	get_cmd_list(&cmd_list, token_list);
	ft_lstclear(&token_list, clear_token);
	return (cmd_list);
}
