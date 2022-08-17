/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:23:55 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/16 03:01:42 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

void	execute_pipe_bin(t_pipe *pipes, t_all *all)
{
	pid_t	pid;
	char	*full_path;

	pid = fork();
	if (pid == -1)
		ft_puterror("fork");
	if (pid == 0)
	{
		dup2(pipes->fd_in, 0);
		dup2(pipes->fd_out, 1);
		full_path = get_full_path(pipes->command, pipes->env);
		if (!full_path)
			ft_error_exit("can't find command", pipes->command);
		if (execve(full_path, pipes->line, pipes->env) == -1)
			ft_error_exit("can't execute command", pipes->command);
	}
	else
		waitpid(pid, &all->exit_status, 0);
}

int	choose_out_in(t_pipe *pipes, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == ">")
			if (ft_to_file(redir, &pipes->fd_out, 1, 0))
				return (error_exit());
		else if (redir->type == ">>")
			if (ft_to_file(redir, &pipes->fd_out, 1, 0))
				return (error_exit());
		else if (redir->type == "<")
			if (read_from_file(redir, &pipes->fd_in, 0))
				return (error_exit());
		else if (redir->type == "<<")
			if (make_heredoc(pipes, redir))
				return (error_exit());
		redir = redir->next;
	}
	return (0);
}

int	make_pipes(t_pipe	*pipes)
{
	t_pipe	*tmp_pipe;
	int		pipe_fd[2];

	tmp_pipe = pipes;
	if (pipe(pipe_fd) < 0)
		return (ft_puterror("can't create new pipe"));
	tmp_pipe->fd_in = STDIN_FILENO;
	tmp_pipe->fd_out = pipe_fd[0];
	tmp_pipe = tmp_pipe->next;
	while (tmp_pipe->next)
	{
		if (pipe(pipe_fd) < 0)
			return (ft_puterror("can't create new pipe"));
		tmp_pipe->fd_in = pipe_fd[0];
		tmp_pipe->fd_out = pipe_fd[1];
		tmp_pipe = tmp_pipe->next;
	}
	tmp_pipe->fd_in = pipe_fd[1];
	tmp_pipe->fd_out = STDOUT_FILENO;
	return (0);
}

int	pipe_executor(t_all *all)
{
	t_pipe	*pipes;

	pipes = all->pipes;
	make_pipes(pipes);
	while (pipes)
	{
		if (pipes->redir)
			choose_out_in(pipes, pipes->redir);
		if (pipes->command)
		{
			if (!execute_build(pipes))
				execute_pipe_bin(pipes, all);
			if (!isatty(pipes->fd_in))
				close(pipes->fd_in);
			if (!isatty(pipes->fd_out))
				close(pipes->fd_out);
		}
		pipes = pipes->next;
	}
	return (0);
}
