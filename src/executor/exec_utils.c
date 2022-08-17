/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 02:35:32 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/16 03:05:17 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

void	ft_error_exit(char *error, char *cmd)
{
	printf("%s - %s", error, cmd);
	exit(1);
}

int	read_from_file(t_redir *redir, int *fd, int need_dup)
{
	*fd = open(redir->file, O_RDONLY);
	if (*fd == -1)
		return (ft_puterror("file error"));
	if (need_dup)
	{
		if (dup2(*fd, STDIN_FILENO) == -1)
			return (ft_puterror(""));
		close(*fd);
	}
	return (0);
}

int	ft_to_file(t_redir *redir, int *fd, int flag, int need_dup)
{
	if (flag)
		*fd = open(redir->file, O_CREAT | O_TRUNC
				| O_RDONLY | O_WRONLY, 0644);
	else
		*fd = open(redir->file, O_CREAT | O_RDONLY
		| O_WRONLY | O_APPEND, 0644);
	if (*fd == -1)
		return (ft_puterror(""));
	if (need_dup)
	{
		if (dup2(*fd, STDOUT_FILENO) == -1)
			return (ft_puterror(""));
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
		tmp_env->next;
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
