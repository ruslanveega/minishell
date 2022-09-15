/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   without_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 00:46:25 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/15 15:55:58 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	make_heredoc2(t_redir *redir)
{
	char	*heredoc;

	signal(SIGINT, (void *)&handler_heredoc2);
	heredoc = NULL;
	heredoc = readline("heredoc>");
	rl_on_new_line();
	while (heredoc)
	{
		if (ft_strcmp(heredoc, redir->file) == 0)
			break ;
		free(heredoc);
		if (g_all->err_str->exit_status == 1)
			break ;
		heredoc = readline("heredoc>");
	}
}

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
		else if (redir->type == REDIRECT_HEREDOC)
			make_heredoc2(redir);
		redir = redir->next;
	}
	free_redirs(tmp_redir);
	clear_cmd_list(tmp_cmd);
}
