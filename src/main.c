/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/08/11 04:44:27 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *all, char *envp[])
{
	all->env = get_env_var(envp);
	// all->exit = 0;
	all->exit_status = 0;
	all->pipes = NULL;
	all->args = NULL;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	*all;
	char	*line;

	(void) argc;
	(void) argv;

	all = malloc(sizeof(t_all));
	if (!all)
		return (error_func("allocation"));
	init_all(all, envp);
	while (1)
	{
		line = readline("");
		all->pipes = init_pipes(line);
		start_executor(all);
		free_line_and_pipe(all);
	}
	return (0);
}
