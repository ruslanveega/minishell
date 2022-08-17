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
	t_token	*current;
	t_token	*next;

	if (!token_list)
		return;
	while (token_list)
	{
		current = (t_token *)token_list->content;
		if (is_redirect(current->key))
		{
			if (!token_list->next)
			{
				printf("bash: syntax error near unexpected token \'newline\'\n");
				exit(1);
			}
			next = (t_token *)token_list->next->content;
			if (next->key != WORD)
			{
				print_error_message(next->key);
				exit(1);
			}
		}
		token_list = token_list->next;
	}
}

static void evaluate_pipes(t_list *token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list)
		return;
	current = (t_token *)token_list->content;
	if (current->key == PIPE)
	{
		printf("bash: syntax error near unexpected token \'|\'\n");
		exit(1);
	}
	while (token_list->next)
	{
		current = (t_token *)token_list->content;
		next = (t_token *)token_list->next->content;
		if (current->key == PIPE && next->key == PIPE)
		{
			printf("bash: syntax error near unexpected token \'|\'\n");
			exit(1);
		}
		token_list = token_list->next;
	}
	if (token_list->next && next->key == PIPE)
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