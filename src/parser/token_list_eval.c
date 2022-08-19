/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_eval.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:13:42 by cdell             #+#    #+#             */
/*   Updated: 2022/08/12 09:13:43 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	print_error_message(int key)
{
	if (key == 0)
		printf("bash: syntax error near unexpected token \'newline\'\n");
	else if (key == REDIRECT_IN)
		printf("bash: syntax error near unexpected token \'<\'\n");
	else if (key == REDIRECT_OUT)
		printf("bash: syntax error near unexpected token \'>\'\n");
	else if (key == REDIRECT_APPEND)
		printf("bash: syntax error near unexpected token \'>>\'\n");
	else if (key == REDIRECT_HEREDOC)
		printf("bash: syntax error near unexpected token \'<<\'\n");
}

static void evaluate_redirect(t_list *token_list)
{
	if (!token_list)
		return;
	while (token_list)
	{
		if (is_redirect(get_token_key(token_list)))
		{
			if (!token_list->next)
			{
				printf("bash: syntax error near unexpected token \'newline\'\n");
				exit(1);
			}
			if (get_token_key(token_list->next) != WORD)
			{
				print_error_message(get_token_key(token_list->next));
				exit(1);
			}
		}
		token_list = token_list->next;
	}
}

static void evaluate_pipes(t_list *token_list)
{
	if (!token_list)
		return;
	if (get_token_key(token_list) == PIPE)
	{
		printf("bash: syntax error near unexpected token \'|\'\n");
		exit(1);
	}
	while (token_list->next)
	{
		if (get_token_key(token_list) == PIPE
		&& get_token_key(token_list->next) == PIPE)
		{
			printf("bash: syntax error near unexpected token \'|\'\n");
			exit(1);
		}
		token_list = token_list->next;
	}
	if (get_token_key(token_list) == PIPE)
	{
		printf("bash: syntax error near unexpected token \'|\'\n");
		exit(1);
	}
}

void	evaluate_token_list(t_list *token_list)
{
	evaluate_pipes(token_list);
	evaluate_redirect(token_list);
}