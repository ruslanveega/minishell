/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:29:29 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/17 06:16:08 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

void	file_execution(t_all *g_all)
{
	t_redir	*redir;
	t_pipe	*tmp_pipe;

	tmp_pipe = g_all->pipes;
	redir = tmp_pipe->redir;
	while (redir != NULL)
	{
		if (redir->type == REDIRECT_OUT)
			ft_to_file(redir, &tmp_pipe->fd_out, TRUE);
		else if (redir->type == REDIRECT_APPEND)
			ft_to_file(redir, &tmp_pipe->fd_in, FALSE);
		else if (redir->type == REDIRECT_IN)
			read_from_file(redir, &tmp_pipe->fd_in);
		else if (redir->type == REDIRECT_HEREDOC)
			make_heredoc(g_all->pipes, redir);
		redir = redir->next;
	}
}

void	execute_bin(t_pipe *pipes)
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
		save_exit_status(pid);
}

void	execute_single(t_all *g_all)
{
	g_all->pipes->fd_in = STDIN_FILENO;
	g_all->pipes->fd_out = STDOUT_FILENO;
	if (g_all->pipes->redir)
	{
		file_execution(g_all);
		if (g_all->err_str->code != NULL)
			return ;
	}
	if (g_all->pipes->command)
	{
		if (execute_build(g_all->pipes))
			execute_bin(g_all->pipes);
	}
}

void	start_executor(t_all *g_all)
{
	if (g_all->pipes->next)
		pipe_executor(g_all);
	else
		execute_single(g_all);
}
