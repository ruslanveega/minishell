/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:59:47 by cdell             #+#    #+#             */
/*   Updated: 2022/08/21 01:00:31 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen_plus(const char *str, char c)
{
	size_t	length;

	length = 0;
	while (str[length] && str[length] != c)
		length++;
	return (length);
}

void print_env_list(t_sl_list *env_var_list)
{
	if (!env_var_list)
	{
		printf("ENV var list is empty\n");
		exit(EXIT_FAILURE);
	}
	while (env_var_list)
	{
		printf("%s=%s\n", (char *)env_var_list->key, (char *)env_var_list->value);
		env_var_list = env_var_list->next;
	}
}

t_sl_list	*get_env_var(char *env[])
{
	int			i;
	size_t		size[2];
	t_sl_list	*env_var_list;
	char		*key;
	char		*value;

	i = 0;
	env_var_list = NULL;
	while (env[i])
	{
		size[0] = ft_strlen_plus(env[i], '=');
		size[1] = ft_strlen(env[i] + size[0]);
		key = malloc(sizeof(char) * size[0] + 1);
		value = malloc(sizeof(char) * size[1] + 1);
		if (!key || !value)
			ft_puterror("Failed to allocate memory in *get_env_var(char *env[]) function");
		ft_strlcpy(key, env[i], size[0] + 1);
		ft_strlcpy(value, env[i] + size[0] + 1, size[1] + 1);
		lst_append_node(&env_var_list, (void *)key, (void *)value);
		i++;
	}
	return (env_var_list);
}
