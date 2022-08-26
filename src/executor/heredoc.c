/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 00:02:14 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/26 03:06:05 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	heredoc_child(t_pipe *pipes, t_redir *redir, int heredoc_fd)
{
	signal(SIGINT, &handler_heredoc);
	pipes->heredoc = readline("heredoc>");
	rl_on_new_line();
	while (!ft_strcmp(pipes->heredoc, redir->file))
	{
		ft_putstr_fd(pipes->heredoc, heredoc_fd);
		ft_putstr_fd("\n", heredoc_fd);
		free(pipes->heredoc);
		pipes->heredoc = readline("heredoc>");
	}
	exit(SUCCES);
}

int	make_heredoc(t_pipe *pipes, t_redir *redir)
{
	pid_t	pid;
	int		heredoc_fd[2];

	if (pipes->fd_in != 0)
		close(pipes->fd_in);
	pipe(heredoc_fd);
	pipes->fd_in = heredoc_fd[0];
	signal(SIGINT, &signal_sigint);
	pid = fork();
	if (pid < 0)
		init_error();
	if (pid == 0)
		heredoc_child(pipes, redir, heredoc_fd[1]);
	waitpid(pid, &err_str->exit_status, 0);
	close(heredoc_fd[1]);
	signal(SIGINT, (void *) &signal_sigint);
	return (err_str->exit_status / 256);
}
