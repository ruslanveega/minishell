/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 00:02:14 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/21 01:05:14 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	make_heredoc(t_pipe *pipe, t_redir *redir)
{
	pid_t	pid;


	pid = fork();
	if (pid < 0)
		init_error();
	if (pid == 0)
	{

	}
}
