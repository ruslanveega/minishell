/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:23:55 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/15 05:15:30 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

void	choose_out_in(t_pipe *pipes, t_redir *redir)
{
	while (redir)
	{
		if (redir->type == REDIRECT_OUT)
			ft_to_file(redir, &pipes->fd_out, TRUE);
		else if (redir->type == REDIRECT_APPEND)
			ft_to_file(redir, &pipes->fd_out, FALSE);
		else if (redir->type == REDIRECT_IN)
			read_from_file(redir, &pipes->fd_in);
		else if (redir->type == REDIRECT_HEREDOC)
			make_heredoc(pipes, redir);
		redir = redir->next;
	}
}

pid_t	*make_pids(int len)
{
	pid_t	*pids;
	int		i;

	pids = (pid_t *)malloc(sizeof(pid_t) * (len + 1));
	if (!pids)
		init_err(MEM_ERR, "", 1, 1);
	i = 0;
	while (i <= len)
		pids[i++] = 0;
	return (pids);
}

int	make_pipes(t_pipe *pipes)
{
	t_pipe	*tmp_pipe;
	int		pipe_fd[2];
	int		len;

	len = 1;
	tmp_pipe = pipes;
	if (pipe(pipe_fd) < 0)
		return (init_err("can't create new pipe", NULL, 1, 1));
	tmp_pipe->fd_in = STDIN_FILENO;
	tmp_pipe->fd_out = pipe_fd[1];
	tmp_pipe = tmp_pipe->next;
	while (tmp_pipe->next)
	{
		tmp_pipe->fd_in = pipe_fd[0];
		if (pipe(pipe_fd) < 0)
			return (init_err("can't create new pipe", NULL, 1, 1));
		tmp_pipe->fd_out = pipe_fd[1];
		tmp_pipe = tmp_pipe->next;
		len++;
	}
	tmp_pipe->fd_in = pipe_fd[0];
	tmp_pipe->fd_out = STDOUT_FILENO;
	g_all->pids = make_pids(len++);
	return (0);
}

void	execute_pipe_bin(t_pipe *pipes, int num)
{
	pid_t	pid;
	char	*full_path;

	pid = fork();
	if (pid == -1)
		init_err("can't create new process", NULL, 1, 1);
	if (pid == 0)
	{
		dup2(pipes->fd_in, 0);
		dup2(pipes->fd_out, 1);
		full_path = get_full_path(pipes->command, g_all->env);
		if (!full_path)
			init_err(ERR_CMD_NOT_FOUND, pipes->command, 1, 1);
		if (execve(full_path, pipes->line, env_to_arr(g_all->env)) == -1)
			init_err(ERR_CMD_NOT_FOUND, pipes->command, 1, 1);
	}
	else
		g_all->pids[num] = pid;
}

int	pipe_executor(t_all *g_all)
{
	t_pipe	*pipes;
	int		i;

	pipes = g_all->pipes;
	make_pipes(pipes);
	i = 0;
	while (pipes)
	{
		if (pipes->redir)
			choose_out_in(pipes, pipes->redir);
		if (g_all->err_str->code != NULL)
			return (1);
		if (execute_build(pipes))
			execute_pipe_bin(pipes, i++);
		if (!isatty(pipes->fd_in))
			close(pipes->fd_in);
		if (!isatty(pipes->fd_out))
			close(pipes->fd_out);
		pipes = pipes->next;
	}
	i = 0;
	while (g_all->pids[i])
		waitpid(g_all->pids[i++], &g_all->err_str->exit_status, 0);
	return (0);
}
