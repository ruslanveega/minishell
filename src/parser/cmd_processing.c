/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:33:02 by cdell             #+#    #+#             */
/*   Updated: 2022/08/16 22:33:04 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void nullify(t_list **redirect_list, char ***cmd_options, int *index)
{
	*redirect_list = NULL;
	*cmd_options = NULL;
	*index = 0;
}

static void add_redirect_node(t_list *token_list, t_list **redirect_list)
{
	t_redirect *redirect;
	t_list *new_node;

	redirect = process_redirect(token_list);
	new_node = ft_lstnew((void *)redirect);
	if (!new_node)
		ft_puterror("Could not allocate memory in parser.c->get_cmd_list");
	ft_lstadd_back(redirect_list, new_node);
}

static int get_arr_size(t_list *token_list)
{
	t_token *token;
	int size;

	size = 0;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->key == PIPE)
			break;
		else if (is_redirect(token->key))
			token_list = token_list->next->next;
		else
		{
			size++;
			token_list = token_list->next;
		}
	}
	return (size);
}

static void process_cmd(t_list *token_list, char *cmd_options[], int index)
{
	t_token *token;
	char *str;

	token = (t_token *)token_list->content;
	str = ft_strdup(token->value);
	if (str)
		cmd_options[index] = str;
}

void get_cmd_list(t_cmd_list **cmd_list, t_list *token_list)
{
	t_list *redirect_list;
	char **cmd_options;
	int index;

	while (token_list)
	{
		//		redirect_list = NULL;
		//		cmd_options = NULL;
		//		index = 0;
		nullify(&redirect_list, &cmd_options, &index);
		cmd_options = (char **)malloc(sizeof(char *) * get_arr_size(token_list) + 1);
		while (token_list && get_token_key(token_list) != PIPE)
		{
			if (is_redirect(get_token_key(token_list)))
			{
				add_redirect_node(token_list, &redirect_list);
				token_list = token_list->next;
			}
			else if (get_token_key(token_list) == WORD)
				process_cmd(token_list, cmd_options, index++);
			token_list = token_list->next;
		}
		cmd_options[index] = NULL;
		add_cmd(cmd_list, redirect_list, cmd_options);
		if (token_list)
			token_list = token_list->next;
	}
}
