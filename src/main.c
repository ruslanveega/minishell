/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/08/17 02:04:43 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_all(t_all *all, char *envp[])
{
	all->env = get_env_var(envp);
	all->exit_status = 0;
	all->pipes = NULL;
}

void	make_pipe_args(t_pipe *pipe, t_cmd_list *cmd, t_env_var *env)
{
	pipe->env = env;
	pipe->redir = cmd->redirect;
	pipe->command = cmd->cmd_options[0];
	pipe->line = cmd->cmd_options;
	pipe->error = NULL;
	pipe->next = NULL;
}

int	init_pipes(t_cmd_list *cmd_list, t_all *all)
{
	t_pipe	*tmp_pipe;

	all->pipes = malloc(sizeof(t_pipe));
	if (!pipe)
		ft_puterror("allocation error");
	tmp_pipe = all->pipes;
	while (cmd_list)
	{
		make_pipe_args(all->pipes, cmd_list, all->env);
		if (cmd_list->next)
		{
			all->pipes->next = malloc(sizeof(t_pipe));
			if (!all->pipes->next)
				return (ft_puterror("allocation error"));
			all->pipes = all->pipes->next;
			cmd_list = cmd_list->next;
		}
	}
	all->pipes = tmp_pipe;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all		*all;
	t_env_var	*env_var;
	char		*line;
	t_cmd_list	*cmd_list;

	(void) argc;
	(void) argv;

	all = malloc(sizeof(t_all));
	if (!all)
		return (ft_puterror("allocation error"));
	env_var = get_env_var(envp);
	init_all(all, envp);
	while (1)
	{
		line = readline("");
		cmd_list = parse_input(line);
		if (init_pipes(cmd_list, all))
			//error();
		start_executor(all);
		free_line_and_pipe(all);
	}
	free_all_and_env(all);
	return (0);
}
