/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:35:32 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/13 05:07:22 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

char	**env_to_arr(t_sl_list *env)
{
	int			env_size;
	char		**env_arr;
	t_sl_list	*tmp_env;
	int			i;

	i = 0;
	env_size = 0;
	tmp_env = env;
	while (tmp_env)
	{
		env_size++;
		tmp_env = tmp_env->next;
	}
	env_arr = malloc(sizeof(char *) * env_size + 1);
	if (!env_arr)
		init_err(MEM_ERR, "", 1, 1);
	while (env)
	{
		env_arr[i++] = ft_strjoin(env->key, "=", env->value);
		env = env->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

int	read_from_file(t_redir *redir, int *fd)
{
	if (access((const char *)redir->file, F_OK) < 0)
		return (init_err(NOT_FILE, redir->file, 0, 1));
	if (access((const char *)redir->file, R_OK) < 0)
		return (init_err(PERM, redir->file, 0, 1));
	*fd = open(redir->file, O_RDONLY);
	return (0);
}

int	ft_to_file(t_redir *redir, int *fd, int flag)
{
	if (access((const char *)redir->file, F_OK) < 0)
		return (init_err(NOT_FILE, redir->file, 0, 1));
	if (access((const char *)redir->file, W_OK) < 0)
		return (init_err(PERM, redir->file, 0, 1));
	if (flag)
		*fd = open(redir->file, O_CREAT | O_TRUNC
				| O_RDONLY | O_WRONLY, 0644);
	else
		*fd = open(redir->file, O_CREAT | O_RDONLY
				| O_WRONLY | O_APPEND, 0644);
	return (0);
}

char	**parse_path(t_sl_list *env)
{
	t_sl_list	*tmp_env;
	char		**path;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->key, "PATH", 4) == 0)
		{
			path = ft_split(tmp_env->value, ':');
			return (path);
		}
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*get_full_path(char *cmd, t_sl_list *env)
{
	char		*full_path;
	char		**paths;
	int			i;

	i = 0;
	paths = parse_path(env);
	if (ft_strchr(cmd, '/'))
	{
		full_path = ft_strdup(cmd);
		return (full_path);
	}
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/", cmd);
		if (access(full_path, F_OK) == 0)
		{
			free(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}
