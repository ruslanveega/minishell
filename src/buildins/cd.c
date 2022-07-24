/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:35 by fcassand          #+#    #+#             */
/*   Updated: 2022/07/22 03:24:59 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	update_pwd(t_sl_list *env, char *key, char *path, int num_sym)
{
	char		cwd[100];
	t_sl_list	*env_tmp;

	if (!path)
	{
		if (getcwd(cwd, 100) == NULL)
			return (error_func());
		path = cwd;
	}
	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->key, key, num_sym) == 0)
		{
			env_tmp->value = path;
			return (0);
		}
		env_tmp = env_tmp->next;
	}
	return (error_func());
}

char	*env_path(t_sl_list *env, char *key, int num_sym)
{
	t_sl_list	*env_tmp;
	char		*path;

	env_tmp = env;
	while (env_tmp)
	{
		if (ft_strncmp(env_tmp->key, key, num_sym) == 0)
		{
			path = env_tmp->value;
			return (path);
		}
		env_tmp = env_tmp->next;
	}
	return (NULL);
}

int	to_home_or_prev_dir(t_sl_list *env, int old_or_home)
{
	char	*path;

	path = NULL;
	if (old_or_home)
	{
		path = env_path(env, "HOME", 4);
		if (!path)
			return (cd_error("HOME not set"));
	}
	else
	{
		path = env_path(env, "OLDPWD", 6);
		if (!path)
			return (cd_error("OLDPWD not set"));
	}
	update_pwd(env, "OLDPWD", NULL, 6);
	chdir(path);
	update_pwd(env, "PWD", NULL, 3);
	return (0);
}

void	ft_cd(char **line, t_sl_list *env)
{
	char	*old_pwd;

	old_pwd = NULL;
	if (!line[1])
		to_home_or_prev_dir(env, 1);
	if (ft_strcmp(line[1], "-") == 0)
		to_home_or_prev_dir(env, 0);
	else
	{
		old_pwd = env_path(env, "OLDPWD", 6);
		if (chdir(line[1]) != 0)
			cd_error(line);
		else
		{
			if (old_pwd)
				update_pwd(env, "OLDPWD", old_pwd, 6);
			update_pwd(env, "PWD", NULL, 3);
		}
	}
}
