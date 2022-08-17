/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 09:13:46 by cdell             #+#    #+#             */
/*   Updated: 2022/08/12 09:13:47 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void expand_db_quotes(t_token *db_quotes_node)
{
	char	*str;

	if (db_quotes_node->value)
	{
		str = get_str_from_db_quotes((char *)db_quotes_node->value);
		free(db_quotes_node->value);
		db_quotes_node->value = str;
	}
	db_quotes_node->key = WORD;
}

static void	expand_env_var(t_token *env_var_token)
{
	char	*env_var_value;

	env_var_value = substitute_env_var_val(env_var_token->value, NULL);
	free(env_var_token->value);
	env_var_token->value = env_var_value;
	env_var_token->key = WORD;
	env_var_value = NULL;
}

void	expand_token_list(t_list *token_list)
{
	t_token	*token;

	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->key == SINGLE_QUOTE
			|| token->key == EXIT_STATUS)
			token->key = WORD;
		else if (token->key == ENV_VAR)
			expand_env_var(token);
		else if (token->key == DOUBLE_QUOTE)
			expand_db_quotes(token);
		token_list = token_list->next;
	}
}