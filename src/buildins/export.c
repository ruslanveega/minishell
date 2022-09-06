/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:19 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/05 01:46:12 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*export_error(char *error, char *line)
{
	if (line)
		printf("%s %s", error, line);
	return (NULL);
}

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
	// char		*key;
	char		*value;
	int			len;
	char		*tmp;

	len = 0;
	value = ft_strchr(line, '=');
	if (!value)
		return (NULL);
	value++;
	new_env = malloc(sizeof(t_sl_list));
	if (!new_env)
		return (export_error("allocation", NULL));
	new_env->value = value;
	tmp = line;
	if (ft_isdigit(line[0]))
		return (export_error("export: not an identifier: ", line));
	while (*line != '=')
		len++;
	*line = '\0';
	new_env->key = ft_strjoin("", tmp, "");
	if (!new_env->key)
		return (export_error("allocation", NULL));
	return (new_env);
}

void	ft_export(char **line, t_sl_list *env)
{
	int			len;
	int			i;
	t_sl_list	*new_env;

	if (!line[1])
	{
		ft_env(env, 1);
		return ;
	}
	len = num_args(line);
	i = 1;
	new_env = NULL;
	while (i <= len)
	{
		new_env = valid_env(line[i]);
		if (new_env)
			env_add_back(env, new_env);
		i++;
	}
}
