/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   without_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 00:46:25 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/14 01:30:23 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	heredoc_child(t_pipe *pipes, t_redir *redir, int heredoc_fd)
// {
// 	signal(SIGINT, (void *)&handler_heredoc);
// 	pipes->heredoc = readline("heredoc>");
// 	rl_on_new_line();
// 	while (!ft_strcmp(pipes->heredoc, redir->file))
// 	{
// 		ft_putstr_fd(pipes->heredoc, heredoc_fd);
// 		ft_putstr_fd("\n", heredoc_fd);
// 		free(pipes->heredoc);
// 		pipes->heredoc = readline("heredoc>");
// 	}
// 	exit(SUCCESS);
// }

// int	make_heredoc2(t_redir *redir)
// {
// 	pid_t	pid;
// 	int		heredoc_fd[2];

// 	if (pipes->fd_in != 0)
// 		close(pipes->fd_in);
// 	pipe(heredoc_fd);
// 	pipes->fd_in = heredoc_fd[0];
// 	signal(SIGINT, (void *)&signal_sigint);
// 	pid = fork();
// 	if (pid < 0)
// 		init_err("can't create new process", "", 1, 1);
// 	if (pid == 0)
// 		heredoc_child(pipes, redir, heredoc_fd[1]);
// 	waitpid(pid, &g_all->err_str->exit_status, 0);
// 	close(heredoc_fd[1]);
// 	signal(SIGINT, (void *)&signal_sigint);
// 	return (g_all->err_str->exit_status / 256);
// }

int	read_from_file2(t_redir *redir)
{
	int	fd;

	if (access((const char *)redir->file, F_OK) < 0)
		return (init_err(NOT_FILE, redir->file, 0, 1));
	if (access((const char *)redir->file, R_OK) < 0)
		return (init_err(PERM, redir->file, 0, 1));
	fd = open(redir->file, O_RDONLY);
	close(fd);
	return (0);
}

int	ft_to_file2(t_redir *redir, int flag)
{
	int	fd;

	if (access((const char *)redir->file, F_OK) < 0)
		return (init_err(NOT_FILE, redir->file, 0, 1));
	if (access((const char *)redir->file, W_OK) < 0)
		return (init_err(PERM, redir->file, 0, 1));
	if (flag)
		fd = open(redir->file, O_CREAT | O_TRUNC
				| O_RDONLY | O_WRONLY, 0644);
	else
		fd = open(redir->file, O_CREAT | O_RDONLY
				| O_WRONLY | O_APPEND, 0644);
	close(fd);
	return (0);
}

void	without_cmd(t_redir *redir, t_cmd_list *tmp_cmd)
{
	t_redir	*tmp_redir;

	tmp_redir = redir;
	while (redir != NULL)
	{
		if (redir->type == REDIRECT_OUT)
			ft_to_file2(redir, TRUE);
		else if (redir->type == REDIRECT_APPEND)
			ft_to_file2(redir, FALSE);
		else if (redir->type == REDIRECT_IN)
			read_from_file2(redir);
		// else if (redir->type == REDIRECT_HEREDOC)
		// 	make_heredoc2(redir);
		// redir = redir->next;
	}
	free_redirs(tmp_redir);
	clear_cmd_list(tmp_cmd);
}
