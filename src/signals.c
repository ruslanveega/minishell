/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 23:54:31 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/15 06:04:23 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handler_heredoc(int sig)
{
	(void)sig;
	ft_putendl_fd("", 1);
	rl_on_new_line();
	exit(1);
	return (0);
}

// int	signal_sigint(int sig)
// {
// 	(void)sig;
// 	rl_on_new_line();
// 	rl_redisplay();
// 	printf("\n");
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// 	g_all->err_str->exit_status = 1;
// 	return (0);
// }

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
// void	ft_signal_cltr_c(int sig)
// {
// 	(void)sig;
// 	g_all->err_str->exit_status = 1;
// 	write(1, "\n", 1);
// 	g_all->err_str->exit_status = 1;
// }

// void	ft_sigquit(int sig)
// {
// 	write(1, "\b\b  \b\b", 6);
// 	write(1, "^\\Quit: ", 8);
// 	ft_putnbr_fd(sig, 1);
// 	write(1, "\n", 1);
// 	// g_signal = 131;
// }

// void	ft_sigterm(int sig)
// {
// 	(void)sig;
// }

// void	ft_signal_sigchld(int sig)
// {
// 	(void)sig;
// }

// void	init_signals(void)
// {
// 	signal(SIGQUIT, (void *)&ft_signal_quit);
// 	signal(SIGCHLD, (void *)&ft_signal_sigchld);
// 	signal(SIGTERM, (void *)&ft_sigterm);
// }

// void	parser_sigint(int sig)
// {
// 	(void)sig;
// 	g_interrupted = 1;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	write(2, "\n", 1);
// 	rl_redisplay();
// 	g_exit_status = 1;
// 	signal(SIGINT, parser_sigint);
// }

// void	parser_sighandler(void)
// {
// 	signal(SIGINT, parser_sigint);
// 	signal(SIGQUIT, SIG_IGN);
// }
