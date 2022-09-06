/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:35:32 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/05 04:36:44 by fcassand         ###   ########.fr       */
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
	env_arr = malloc(sizeof(char *) * env_size);
	if (!env_arr)
		init_err(MEM_ERR, "", 1, 1);
	while (env)
	{
		env_arr[i++] = ft_strjoin(env->key, "=", env->key);
		env = env->next;
	}
	return (env_arr);
}

int	read_from_file(t_redir *redir, int *fd, int need_dup)
{
	if (access((const char *)redir->file, F_OK) < 0)
		return (init_err(NOT_FILE, redir->file, 0, 1));
	if (access((const char *)redir->file, R_OK) < 0)
		return (init_err(PERM, redir->file, 0, 1));
	*fd = open(redir->file, O_RDONLY);
	if (need_dup)
	{
		if (dup2(*fd, STDIN_FILENO) == -1)
			return (init_err(DUP, redir->file, 0, 1));
		close(*fd);
	}
	return (0);
}

int	ft_to_file(t_redir *redir, int *fd, int flag, int need_dup)
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
	if (need_dup)
	{
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (init_err(DUP, redir->file, 0, 1));
		close(*fd);
	}
	return (0);
}

char	**parse_path(t_sl_list *env)
{
	t_sl_list	*tmp_env;
	char		**path;

	tmp_env = env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->key, "PATH=", 5) == 0)
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
