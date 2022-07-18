/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:35 by fcassand          #+#    #+#             */
/*   Updated: 2022/07/18 19:59:48 by fcassand         ###   ########.fr       */
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



int	to_home_or_prev_dir(t_sl_list *env, int old_or_home)
{
	char	*path;

	path = NULL;
	if (old_or_home)
	{
		path = env_path(env, "HOME", 4);
		if (!path)
			return(cd_error("HOME not set"));
	}
	else
	{
		path = env_path(env, "OLDPWD", 6);
		if (!path)
			return(cd_error("OLDPWD not set"));
	}
	chdir(path);
	return (0);
}

void	to_path(char *path, t_sl_list *env)
{

}

void	ft_cd(char **line, t_sl_list *env)
{
	if (!line[1])
		to_home_or_prev_dir(env, 1);
	if (ft_strcmp(line[1], "-") == 0)
		to_home_or_prev_dir(env, 0);
	else
		to_path(line[1], env);
	if (chdir(line[1]) != 0)
		cd_error(line);
}

// chdir, getcwd
// нужно изменить env oldpwd && pwd
