/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toke_key_getter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:33:53 by cdell             #+#    #+#             */
/*   Updated: 2022/08/16 22:33:55 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int get_token_key(t_list *token_list)
{
	t_token *token;

	token = (t_token *)token_list->content;
	return (token->key);
}
