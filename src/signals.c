/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:54:31 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/21 04:00:46 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handler_readline_heredoc(int sig)
{
	// (void)sig;
	// if (!g_shell->buffer)
	// 	free(g_shell->buffer);
	// g_shell->buffer = NULL;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	exit(1);
	return (0);
}

int	signal_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return (0);
}

void	init_signals(void)
{
	signal(SIGINT, (void *)&signal_sigint);
	signal(SIGQUIT, SIG_IGN);
}
