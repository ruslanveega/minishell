/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utlis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:26:51 by cdell             #+#    #+#             */
/*   Updated: 2022/06/28 17:26:54 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int	get_space_token(char **str)
{
	while (**str && ft_strchr(WHITE_SPACE_CHARS, **str))
		(*str)++;
	return (WHITE_SPACE);
}

int	get_word_token(char **str)
{
	int	token;

	token = WORD;
	if (**str == '$')
	{
		token = ENV_VAR;
		(*str)++;
	}
	while (**str && !ft_strchr(WHITE_SPACE_CHARS, **str) && !ft_strchr(TOKENS, **str))
		(*str)++;
	return (token);
}

int	get_quote_tk(char **str, char quote_type)
{
	int	token;

	token = (int)**str;
	(*str)++;
	while (**str && **str != quote_type)
		(*str)++;
	if (**str == 0)
		ft_puterror("Unclosed QUOTE");
	(*str)++;
	return (token);
}

int	get_redirect_token(char **str)
{
	int	token;

	token = (int)**str;
	if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			token = REDIRECT_APPEND;
			(*str) += 1;
		}
		else if (*(*str + 1) == '<')
			ft_puterror("syntax error near unexpected token '<'");
	}
	else if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			token = REDIRECT_HEREDOC;
			(*str) += 1;
		}
		else if (*(*str + 1) == '>')
			(*str) += 1;
	}
	(*str) += 1;
	return (token);
}
