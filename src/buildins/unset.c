/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:13 by fcassand          #+#    #+#             */
/*   Updated: 2022/07/21 05:21:32 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_env(t_sl_list *env)
{
	env->next = NULL;
	free(env->key);
	free(env->value);
	free(env);
}

void	del_env(char *key, t_sl_list *env, int len)
{
	t_sl_list	*tmp_env;
	t_sl_list	*tmp_env2;

	tmp_env = env;
	while (env)
	{
		if (ft_strncmp(key, env->next->key, len) == 0)
		{
			tmp_env2 = env->next;
			env->next = env->next->next;
			env = tmp_env;
			free_env(tmp_env2);
			return ;
		}
		env = env->next;
	}
}

int	num_args(char **line)
{
	int	num;

	num = 1;
	while (line[num])
		num++;
	return (num);
}

void	ft_unset(char **line, t_sl_list *env)
{
	t_sl_list	*tmp_env;
	int			len;
	int			num_to_del;
	int			i;

	if (!line[1])
		return ;
	num_to_del = num_args(line);
	i = 1;
	while (num_to_del)
	{
		tmp_env = env;
		while (tmp_env)
		{
			len = ft_strlen(line[i]);
			if (ft_strncmp(line[i], tmp_env->key, len) == 0)
				del_env(tmp_env->key, env, len);
			tmp_env->next;
		}
		i++;
		num_to_del--;
	}
}
