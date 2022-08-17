/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Abdu-Rashid <Abdu-Rashid@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:59:47 by cdell             #+#    #+#             */
/*   Updated: 2022/07/30 22:51:19 by Abdu-Rashid      ###   ########.fr       */
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

t_list	*get_env_var(char *env[])
{
	int i;
	size_t size[2];
	t_list	*env_var_list;
	char *key;
	char *value;

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
		append_env_var(&env_var_list, key, value);
		i++;
	}
	return (env_var_list);
}
