/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 01:42:22 by fcassand         ###   ########.fr       */
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
		all->err_str->code = MEM_ERR;
	tmp_pipe = all->pipes;
	while (cmd_list)
	{
		make_pipe_args(all->pipes, cmd_list, all->env);
		if (cmd_list->next)
		{
			all->pipes->next = malloc(sizeof(t_pipe));
			if (!all->pipes->next)
				init_err(MEM_ERR, "", 1, 0);
			all->pipes = all->pipes->next;
			cmd_list = cmd_list->next;
		}
	}
	all->pipes = tmp_pipe;
}

void	mini_loop(t_all *all)
{
	char			*line;
	t_cmd_list		*cmd_list;

	all->err_str = malloc(sizeof(t_error));
	all->err_str->code = NULL;
	all->err_str->exit = 0;
	all->err_str->token = NULL;
	all->err_str->exit_status = 0;
	cmd_list = NULL;
	while (1)
	{
		free_pipe_cmd(all->pipes, cmd_list);
		if (!ft_strcmp(all->err_str->code, MEM_ERR) || all->err_str->exit)
			break ;
		line = readline("minishell$");
		add_history(line);
		cmd_list = parse_input(line, all);
		free(line);
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
	(void) argc;
	(void) argv;
	init_signals();
	all = malloc(sizeof(t_all));
	if (!all)
		all->err_str->code = MEM_ERR;
	all->env = get_env_var(envp);
	all->pipes = NULL;
	incr_shlvl(all, 1);
	mini_loop(all);
	free_all_and_env(all);
	return (0);
}
