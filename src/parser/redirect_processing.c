/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:39:22 by cdell             #+#    #+#             */
/*   Updated: 2022/08/11 06:39:26 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_redirect	*process_redirect(t_list *token_list)
{
	t_redirect	*redirect;
	t_token		*token;

	redirect = (t_redirect *)malloc(sizeof(t_redirect));
	if (!redirect)
		ft_puterror("Failed to allocate memory for redirection in [redirect_processing.c->process_redirect]");
	token = (t_token *)token_list->content;
	if (token->key == REDIRECT_IN)
		redirect->type = REDIRECT_IN;
	else if (token->key == REDIRECT_OUT)
		redirect->type = REDIRECT_OUT;
	else if (token->key == REDIRECT_APPEND)
		redirect->type = REDIRECT_APPEND;
	else if (token->key == REDIRECT_HEREDOC)
		redirect->type = REDIRECT_HEREDOC;
	token = (t_token *)token_list->next->content;
	redirect->file = token->value;
	token = NULL;
	return (redirect);
}

//t_redirect *process_redirect(t_sl_list *token_list)
//{
//	// TODO: depending on the type of the token, return file name or stop word for HEREDOC
//	t_redirect	*redirect;
//
//	redirect = (t_redirect *)malloc(sizeof(t_redirect));
//	if (!redirect)
//		ft_puterror("Failed to allocate memory for redirection in [redirect_processing.c->process_redirect]");
//	if (token_list->key == (void *)REDIRECT_IN)
//		redirect->type = REDIRECT_IN;
//	else if (token_list->key == (void *)REDIRECT_OUT)
//		redirect->type = REDIRECT_OUT;
//	else if (token_list->key == (void *)REDIRECT_APPEND)
//		redirect->type = REDIRECT_APPEND;
//	else if (token_list->key == (void *)REDIRECT_HEREDOC)
//		redirect->type = REDIRECT_HEREDOC;
//	redirect->file = (char *)token_list->next->value;
//	return (redirect);
//}