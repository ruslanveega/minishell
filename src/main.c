/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/08/27 01:19:44 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_pipe_args(t_pipe *pipe, t_cmd_list *cmd, t_sl_list *env)
{
	pipe->env = env;
	pipe->redir = cmd->redirect;
	pipe->command = cmd->cmd_options[0];
	pipe->line = cmd->cmd_options;
	pipe->heredoc = NULL;
	pipe->next = NULL;
}

void	init_pipes(t_cmd_list *cmd_list, t_all *all)
{
	t_pipe	*tmp_pipe;

	all->pipes = malloc(sizeof(t_pipe));
	if (!all->pipes)
		err_str->code = MEM_ERR;
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
}

void	mini_loop(t_all *all, t_sl_list *env)
{
	char			*line;
	t_cmd_list		*cmd_list;

	err_str = malloc(sizeof(t_error));
	err_str->code = NULL;
	err_str->exit = 0;
	err_str->token = NULL;
	err_str->exit_status = 0;
	while (1)
	{
		free_line_and_pipe(all->pipes, line);
		if (err_str->code == MEM_ERR || err_str->exit)
			break ;
		line = readline("minishell$");
		add_history(line);
		cmd_list = parse_input(line);
		if (print_error() || cmd_list == NULL)
			continue ;
		init_pipes(cmd_list, all);
		start_executor(all);
		if (print_error())
			continue ;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all	*all;

	(void) argc;
	(void) argv;
	init_signals();
	all = malloc(sizeof(t_all));
	if (!all)
		err_str->code = MEM_ERR;
	all->env = get_env_var(envp);
	all->pipes = NULL;
	incr_shlvl(all->env, 1);
	mini_loop(all, all->env);
	free_all_and_env(all, all->env);
	return (0);
}
