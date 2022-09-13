/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:19 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/13 04:34:14 by fcassand         ###   ########.fr       */
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

int	search_in_old(t_sl_list *new)
{
	t_sl_list	*old;

	old = g_all->env;
	while (old)
	{
		if (ft_strcmp(new->key, old->key) == 0)
		{
			free(old->value);
			old->value = ft_strdup(new->value);
			free(new->key);
			free(new->value);
			free(new);
			return (1);
		}
		old = old->next;
	}
	return (0);
}

t_sl_list	*valid_env(char *line)
{
	t_sl_list	*new_env;
	char		*value;
	char		*tmp;

	value = ft_strchr(line, '=');
	if (!value)
		return (NULL);
	value++;
	new_env = malloc(sizeof(t_sl_list));
	new_env->value = ft_strdup(value);
	tmp = line;
	if (ft_isdigit(line[0]))
		init_err(ft_strjoin("minishell: ", "export: ",
				INVALID_ARG_FOR_UNSET), line, 0, 1);
	while (*line != '=')
		line++;
	*line = '\0';
	new_env->key = ft_strdup(tmp);
	new_env->next = NULL;
	if (search_in_old(new_env))
		return (NULL);
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
	while (i < len)
	{
		new_env = valid_env(line[i]);
		if (new_env)
			env_add_back(env, new_env);
		i++;
	}
}
