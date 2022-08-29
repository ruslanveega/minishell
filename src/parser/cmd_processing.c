/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_processing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:33:02 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 00:52:12 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	nullify(t_list **redirect_list, char ***cmd_options, int *index)
{
	*redirect_list = NULL;
	*cmd_options = NULL;
	*index = 0;
}

// t_redir	*add_redirect_node(t_list *token_list)
// {
// 	t_redir	*redirect_list;
// 	t_token	*token;

// 	redirect_list = malloc(sizeof(t_redir));
// 	if (!redirect_list)
// 		init_err(MEM_ERR, "", 1, 0);
// 	redirect_list->type = get_token_node_key(token_list);
// 	token = (t_token *)token_list->next->content;
// 	redirect_list->file = ft_strdup(token->value);
// 	if (!redirect_list->file)
// 		init_err(MEM_ERR, "", 1, 0);
// 	redirect_list->next = NULL;
// 	return (redirect_list);
// }

void	add_redirect_node(t_list *token_list, t_redir *redirect_list)
{
	t_redir	*redirect_list;
	t_token	*token;

	while (redirect_list->next)
		redirect_list = redirect_list->next;
	redirect_list->next = malloc(sizeof(t_redir));
	if (!redirect_list->next)
		init_err(MEM_ERR, "", 1, 0);
	redirect_list->next->file = get_token_node_key(token_list);
	token = (t_token *)token_list->next->content;
	redirect_list->next->file = ft_strdup(token->value);
	if (!redirect_list->next->file)
		init_err(MEM_ERR, "", 1, 0);
	redirect_list->next->next = NULL;
}

static int	get_arr_size(t_list *token_list)
{
	t_token	*token;
	int		size;

	size = 0;
	while (token_list)
	{
		token = (t_token *)token_list->content;
		if (token->key == PIPE)
			break ;
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

static void	process_cmd(t_list *token_list, char *cmd_options[], int index)
{
	t_token	*token;
	char	*str;

	token = (t_token *)token_list->content;
	str = ft_strdup(token->value);
	if (str)
		cmd_options[index] = str;
}

void	get_cmd_list(t_cmd_list **cmd_list, t_list *token_list)
{
	t_redir	*redirect_list;
	char	**cmd_options;
	int		index;

	while (token_list)
	{
		nullify(&redirect_list, &cmd_options, &index);
		cmd_options = malloc(sizeof(char *) * get_arr_size(token_list) + 1);
		while (token_list && get_token_node_key(token_list) != PIPE)
		{
			if (is_redirect(get_token_node_key(token_list)))
			{
				add_redirect_node(token_list, redirect_list);
				token_list = token_list->next;
			}
			else if (get_token_node_key(token_list) == WORD)
				process_cmd(token_list, cmd_options, index++);
			token_list = token_list->next;
		}
		cmd_options[index] = NULL;
		append_cmd(cmd_list, redirect_list, cmd_options);
		if (token_list)
			token_list = token_list->next;
	}
}

// void	get_cmd_list(t_cmd_list **cmd_list, t_list *token_list)
// {
// 	t_redir	*redirect_list;
// 	char	**cmd_options;
// 	int		index;
// 	t_redir	*tmp_redir;

// 	tmp_redir = redirect_list;
// 	while (token_list)
// 	{
// 		nullify(&redirect_list, &cmd_options, &index);
// 		cmd_options = malloc(sizeof(char *) * get_arr_size(token_list) + 1);
// 		while (token_list && get_token_node_key(token_list) != PIPE)
// 		{
// 			if (is_redirect(get_token_node_key(token_list)))
// 			{
// 				redirect_list = add_redirect_node(token_list);
// 				token_list = token_list->next;
// 				redirect_list = redirect_list->next;
// 			}
// 			else if (get_token_node_key(token_list) == WORD)
// 				process_cmd(token_list, cmd_options, index++);
// 			token_list = token_list->next;
// 		}
// 		cmd_options[index] = NULL;
// 		append_cmd(cmd_list, tmp_redir, cmd_options);
// 		if (token_list)
// 			token_list = token_list->next;
// 	}
// }
