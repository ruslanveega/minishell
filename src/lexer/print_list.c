/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 16:15:26 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 17:43:48 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	print_token(t_token *token_ls)
{
	if (token_ls->key == WHITE_SPACE)
		printf("token = space\n");
	else if (token_ls->key == WORD)
		printf("token = word\tvalue = %s\n", token_ls->value);
	else if (token_ls->key == ENV_VAR)
		printf("token = ENV_VAR\t value = %s\n", token_ls->value);
	else if (token_ls->key == EXIT_STATUS)
		printf("token = EXIT_STATUS\n");
	else if (token_ls->key == SINGLE_QUOTE)
		printf("token = SINGLE quote\tvalue = %s\n", token_ls->value);
	else if (token_ls->key == DOUBLE_QUOTE)
		printf("token = DOUBLE quote\tvalue = %s\n", token_ls->value);
	else if (token_ls->key == REDIRECT_IN)
		printf("token = <\tvalue Redirection in\n");
	else if (token_ls->key == REDIRECT_OUT)
		printf("token = >\tvalue = Redirection out\n");
	else if (token_ls->key == REDIRECT_APPEND)
		printf("token = >> (APPEND)\n");
	else if (token_ls->key == REDIRECT_HEREDOC)
		printf("token = << (HEREDOC)\n");
	else if (token_ls->key == PIPE)
		printf("token = |\t value = Pipe\n");
}

void	print_list(t_list *token_ls)
{
	t_token	*token;

	token = NULL;
	if (!token_ls)
	{
		printf("Token list is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token_ls)
	{
		token = (t_token *)token_ls->content;
		print_token(token);
		token_ls = token_ls->next;
	}
}
