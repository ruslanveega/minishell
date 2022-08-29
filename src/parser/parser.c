/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:44:37 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 02:17:25 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	process_token_list(t_list *token_list)
{
	t_list	*tokens;

	tokens = token_list;
	expand_token_list(tokens);
	join_token_list(tokens);
	strip_space(tokens);
	if (!evaluate_token_list(tokens))
		return (ERROR);
	return (SUCCESS);
}

t_cmd_list	*parse_input(char *line)
{
	t_cmd_list	*cmd_list;
	t_list		*token_list;

	cmd_list = NULL;
	if (ft_strlen(line) == 0)
		return (NULL);
	token_list = get_token_list(line);
	if (!token_list) {
		return (NULL);
	}
	if (!process_token_list(token_list))
	{
		ft_lstclear(&token_list, clear_token);
		return (NULL);
	}
	get_cmd_list(&cmd_list, token_list);
	ft_lstclear(&token_list, clear_token);
	return (cmd_list);
}
