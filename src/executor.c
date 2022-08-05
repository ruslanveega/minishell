/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:29:29 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/05 05:54:16 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	change_output(t_redir *redir, int *fd)
{
	int	tmp_fd;

	while (redir != NULL)
	{
		if (redir->type == ">")
		{
			tmp_fd = open(redir, W_OK);
			if (!tmp_fd)
			{
				if (dup2())
				close(*fd);
				*fd = tmp_fd;
			}
		}
	}
}

void	file_execution(t_all *all)
{
	t_redir	*redir;
	int		fd_in;
	int		fd_out;

	redir = all->pipes->redir;
	fd_in = 0;
	fd_out = 1;
	if (change_output(redir, &fd_out))
		return (error());



}

void	execute_bin(t_pipe *pipe)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(pipe->command, pipe->line, pipe->env) == -1)
		{
			error();
			exit(1);
		}
	}
}

int	execute_build(t_pipe *pipe)
{
	if (pipe->command == "echo")
		echo(pipe->line);
	else if (pipe->command == "cd")
		ft_cd(pipe->line, pipe->env);
	else if (pipe->command == "env")
		ft_env(pipe->env, 0);
	else if (pipe->command == "exit")
		ft_exit(pipe->line);
	else if (pipe->command == "export")
		ft_export(pipe->line, pipe->env);
	else if (pipe->command == "pwd")
		ft_pwd(pipe->env);
	else if (pipe->command == "unset")
		ft_unset(pipe->line, pipe->env);
	else
		return (0);
	return (1);
}

void	start_executor(t_all *all)
{
	if (all->pipes->next)
		pipe_executor(all);
	else
	{
		if (all->pipes->redir)
			file_execution(all->pipes);
		else if (all->pipes->command)
		{
			if (execute_build(all->pipes))
				return ;
			else
				execute_simle_bin(all->pipes);
		}
		else
			not_execute(all); //cases with $ and var=
	}
}
