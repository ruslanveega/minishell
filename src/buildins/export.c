/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:19 by fcassand          #+#    #+#             */
/*   Updated: 2022/07/21 05:55:48 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	env_add_back(t_sl_list *env, t_sl_list *new_env)
{
	t_sl_list	*tmp;

	tmp = env;
	while (env->next)
		env = env->next;
	env->next = new_env;
	env = tmp;
}

t_sl_list	*valid_env(char *line)
{
	t_sl_list	*new_env;
	char		*key;
	char		*value;
	int			len;
	char		*tmp;

	value = ft_strchr(line, '=');
	if (!value)
		return (NULL);
	value++;
	new_env = malloc(sizeof(t_sl_list));
	if (!new_env)
		return (error("allocation"));
	new_env->value = value;
	tmp = line;
	while (*line != '=')
		len++;
	*line = '\0';
	new_env->key = ft_strjoin("", tmp);
	if (!new_env->key)
		return (error("allocation"));
	return (new_env);
}

int	ft_export(char **line, t_sl_list *env)
{
	int			len;
	int			i;
	t_sl_list	*new_env;

	if (!line[1])
		return (declare(env));
	len = num_args(line);
	i = 1;
	new_env = NULL;
	while (i <= len)
	{
		new_env = valid_env(line[i]);
		if (new_env)
			env_add_backenv(env, new_env);
		i++;
	}
	return (0);
}
