/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 00:02:14 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/19 03:34:28 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_heredoc(t_pipe *pipe, t_redir *redir)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_puterror("fork error");
	if (pid == 0)
	{
		
	}
}
