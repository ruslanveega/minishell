/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:26:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/17 06:48:31 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_build(t_pipe *pipe)
{
	if (!ft_strcmp(pipe->command, "echo"))
		echo(pipe->line);
	else if (!ft_strcmp(pipe->command, "cd"))
		ft_cd(pipe->line, g_all->env);
	else if (!ft_strcmp(pipe->command, "env"))
		ft_env(g_all->env, 0);
	else if (!ft_strcmp(pipe->command, "exit"))
		ft_exit(pipe);
	else if (!ft_strcmp(pipe->command, "export"))
		ft_export(pipe->line, g_all->env);
	else if (!ft_strcmp(pipe->command, "pwd"))
		ft_pwd(g_all->env, pipe->line);
	else if (!ft_strcmp(pipe->command, "unset"))
		ft_unset(pipe->line, g_all->env);
	else
		return (1);
	return (0);
}

void	save_exit_status(pid_t pid)
{
	int	status;

	waitpid(pid, &g_all->err_str->exit_status, WUNTRACED);
	status = g_all->err_str->exit_status;
	if (WIFEXITED(status))
		g_all->err_str->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			g_all->err_str->exit_status = 131;
		else
			g_all->err_str->exit_status = 130;
	}
	else
		g_all->err_str->exit_status = 1;
}

void	exec_last(t_pipe *pipes)
{
	pid_t	pid;
	char	*full_path;

	if (!execute_build(pipes))
		return ;
	pid = fork();
	if (pid == -1)
		init_err("can't create new process", NULL, 1, 1);
	if (pid == 0)
	{
		child_signal();
		dup2(pipes->fd_in, 0);
		dup2(pipes->fd_out, 1);
		full_path = get_full_path(pipes->command, g_all->env);
		if (!full_path)
			init_err(ERR_CMD_NOT_FOUND, pipes->command, 1, 1);
		if (execve(full_path, pipes->line, env_to_arr(g_all->env)) == -1)
			init_err(ERR_CMD_NOT_FOUND, pipes->command, 1, 1);
	}
	else
		save_exit_status(pid);
}
