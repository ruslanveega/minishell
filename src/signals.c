/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:54:31 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/18 02:48:02 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handler_heredoc2(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	g_all->err_str->exit_status = 1;
	return (0);
}

int	handler_heredoc(int sig)
{
	(void)sig;
	if (g_all->pipes->heredoc)
		free(g_all->pipes->heredoc);
	ft_putendl_fd("", 1);
	rl_on_new_line();
	exit(1);
	return (0);
}

void	signal_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_all->err_str->exit_status = 1;
}

void	init_signals(void)
{
	signal(SIGINT, &signal_sigint);
	signal(SIGQUIT, SIG_IGN);
}
