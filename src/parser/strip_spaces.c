/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strip_spaces.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:18:24 by cdell             #+#    #+#             */
/*   Updated: 2022/08/12 16:18:25 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void strip_space(t_list *token_list)
{
	t_list	*tmp;
	t_token		*next;

	while (token_list)
	{
		if (token_list->next)
		{
			next = (t_token *)token_list->next->content;
			if (next->key == WHITE_SPACE)
			{
				tmp = token_list->next;
				token_list->next = token_list->next->next;
				clear_token(tmp->content);
				free(tmp);
			}
		}
		token_list = token_list->next;
	}
}