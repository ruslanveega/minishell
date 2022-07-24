/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/07/24 02:02:26 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_args(char *line)
{
	char	**args;
	int		flag;
	int		len_args;
	int		len_line;
	char	*tmp;

	flag = 0;
	while (*line)
	{
		if (*line == 148 && !flag)
			flag = 2;
		if ((*line == 148 && !flag))
			flag = 1;
		i
		line++;
	}
}

void	init_all(t_all *all, char *envp[])
{
	all->env = get_env_var(envp);
	all->exit = 0;
	all->is_buildin = 0;
	all->pipes = 0;
	all->redir = NULL;
	all->token = NULL;
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
	while (!all->exit)
	{
		line = readline("");
		all->token = get_token_list(line);
		all->args = get_args(ft_strtrim(line, WHITE_SPACE_CHARS));
		free(line);
	}
	return (0);
}
