/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 01:29:29 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/17 04:47:30 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "../minishell.h"

int	file_execution(t_all *all)
{
	t_redir	*redir;

	all->fds[0] = 0;
	all->fds[1] = 1;
	redir = all->pipes->redir;
	while (redir != NULL)
	{
		if (redir->type == REDIRECT_OUT)
			if (ft_to_file(redir, &all->fds[1], TRUE, TRUE))
				return (1);
		else if (redir->type == REDIRECT_APPEND)
			if (ft_to_file(redir, &all->fds[1], FALSE, TRUE))
				return (1);
		else if (redir->type == REDIRECT_IN)
			if (read_from_file(redir, &all->fds[0], TRUE))
				return (1);
		else if (redir->type == REDIRECT_HEREDOC)
			if (make_heredoc(all->pipes, redir))
				return (error_exit());
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
	// else
	// 	not_execute(all); //cases with $ and var=
}

void	start_executor(t_all *all)
{
	if (all->pipes->next)
		pipe_executor(all);
	else
		execute_single(all);
}
