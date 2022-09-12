/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:22 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/12 01:50:50 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_arg(char *line)
{
	if (*line == '+' || *line == '-')
		line++;
	while (*line)
		if (!isdigit(*line++))
			return (1);
	return (0);
}

int	ft_exit(t_pipe *pipes)
{
	char	*tmp;

	tmp = pipes->line[2];
	if (pipes->next || !isatty(pipes->fd_in))
	{
		close(pipes->fd_in);
		close(pipes->fd_out);
		return (1);
	}
	if (get_charr_size(pipes->line) > 2)
		return (init_err(TO_MANY, "", 0, 1));
	if (pipes->line[1] != NULL && check_arg(pipes->line[1]))
		return (init_err(NUM_ARG, pipes->line[1], 1, 1));
	ft_putstr_fd("exit\n", 1);
	exit(EXIT_SUCCESS);
	g_all->err_str->exit = 1;
	return (0);
}
