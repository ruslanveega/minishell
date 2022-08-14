/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:29:29 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/14 21:54:05 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

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

int	file_execution(t_all *all)
{
	t_redir	*redir;

	all->fds[0] = 0;
	all->fds[1] = 1;
	redir = all->pipes->redir;
	while (redir != NULL)
	{
		if (redir->type == ">")
			if (ft_to_file(redir, &all->fds[1], 1, 1))
				return (1);
		else if (redir->type == ">>")
			if (ft_to_file(redir, &all->fds[1], 0, 1))
				return (1);
		else if (redir->type == "<")
			if (read_from_file(redir, &all->fds[0], 1))
				return (1);
		else if (redir->type == "<<")
			if (make_heredoc(all->pipes, redir))
				return (error_exit());
		redir = redir->next;
	}
	return (0);
}

void	execute_bin(t_pipe *pipe)
{
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(pipe->command, pipe->line, pipe->env) == -1)
			ft_puterror(pipe->command);
		exit(1);
	}
}

void	execute_single(t_all *all)
{
	if (all->pipes->redir)
		if (file_execution(all))
			return (ft_puterror(""));
	if (all->pipes->command)
	{
		if (execute_build(all->pipes))
			return ;
		else
			execute_bin(all->pipes);
	}
	else
		not_execute(all); //cases with $ and var=
}

void	start_executor(t_all *all)
{
	if (all->pipes->next)
		pipe_executor(all);
	else
		execute_single(all);
}
