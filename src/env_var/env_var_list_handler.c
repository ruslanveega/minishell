/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_list_handler.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:34:21 by cdell             #+#    #+#             */
/*   Updated: 2022/08/16 22:34:22 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_env_var *create_env_var_node(char *key, char *value)
{
	t_env_var *node;

	node = NULL;
	node = (t_env_var *)malloc(sizeof(t_env_var));
	if (!node)
		ft_puterror("Failed to allocate memory for env_var");
	node->key = key;
	node->value = value;
	return (node);
}

void clear_env_var(t_env_var *env_var_node)
{
	free(env_var_node->key);
	free(env_var_node->value);
	free(env_var_node);
	env_var_node = NULL;
}

void append_env_var(t_list **env_var_list, char *key, char *value)
{
	t_env_var *env_var_node;
	t_list *new_node;

	env_var_node = create_env_var_node(key, value);
	new_node = ft_lstnew((void *)env_var_node);
	ft_lstadd_back(env_var_list, new_node);
}