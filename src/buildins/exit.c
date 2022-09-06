/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:22 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/05 01:44:42 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_arg(char *line)
{
	if (*line == '+' || *line == '-')
		line++;
	while (*line)
		if (!isdigit(*line))
			return (1);
	return (0);
}

int	ft_exit(t_pipe *pipes)
{
	if (pipes->next || !isatty(pipes->fd_in))
	{
		close(pipes->fd_in);
		close(pipes->fd_out);
		return (1);
	}
	ft_putstr_fd("minishell: exit:", 1);
	if (pipes->line[2] != NULL)
		return (init_err(TO_MANY, "", 0, 1));
	if (pipes->line[1] != NULL && check_arg(pipes->line[1]))
		return (init_err(NUM_ARG, pipes->line[1], 1, 1));
	g_all->err_str->exit = 1;
	return (0);
}
