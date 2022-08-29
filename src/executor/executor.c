/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:29:29 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/30 02:24:00 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

int	file_execution(t_all *all)
{
	t_redir	*redir;
	t_pipe	*tmp_pipe;

	tmp_pipe = all->pipes;
	redir = tmp_pipe->redir;
	while (redir != NULL)
	{
		if (redir->type == REDIRECT_OUT)
			if (ft_to_file(redir, &tmp_pipe->fd_out, TRUE, TRUE))
				return (1);
		else if (redir->type == REDIRECT_APPEND)
			if (ft_to_file(redir, &tmp_pipe->fd_in, FALSE, TRUE))
				return (1);
		else if (redir->type == REDIRECT_IN)
			if (read_from_file(redir, &tmp_pipe->fd_in, TRUE))
				return (1);
		else if (redir->type == REDIRECT_HEREDOC)
			if (make_heredoc(all->pipes, redir))
				return (1);
		redir = redir->next;
	}
	return (0);
}

void	execute_bin(t_pipe *pipe)
{
	int		pid;
	char	*full_path;

	pid = fork();
	if (pid == 0)
	{
		full_path = get_full_path(pipe->command, pipe->env);
		if (!full_path)
			ft_error_exit("can't find command", pipe->command);
		if (execve(full_path, pipe->line, pipe->env) == -1)
			ft_error_exit("can't execute command", pipe->command);
	}
	else
		waitpid(pid, &all->err_str->exit_status, 0);
}

void	execute_single(t_all *all)
{
	make_pipes(all->pipes);
	if (all->pipes->redir)
		if (file_execution(all))
			return ;
	if (all->pipes->command)
	{
		if (execute_build(all->pipes))
			execute_bin(all->pipes);
	}
}

void	start_executor(t_all *all)
{
	if (all->pipes->next)
		pipe_executor(all);
	else if (ft_strcmp(all->pipes->command, "minishell") == 0 && \
		!(all->pipes->line[1]))
		incr_shlvl(all, 1);
	else
		execute_single(all);
}
