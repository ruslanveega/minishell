/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 03:34:20 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int err_code = 0;

void	init_all(t_all *all, char *envp[])
{
	t_error	*err_st;

	err_st = malloc(sizeof(t_error));
	err_st->code = 0;
	err_st->error_argument = NULL;
	all->err_st = err_st;
	all->env = get_env_var(envp);
	all->exit_status = 0;
	all->pipes = NULL;
}

void	make_pipe_args(t_pipe *pipe, t_cmd_list *cmd, t_sl_list *env)
{
	pipe->env = env;
	pipe->redir = cmd->redirect;
	pipe->command = cmd->cmd_options[0];
	pipe->line = cmd->cmd_options;
	pipe->heredoc = NULL;
	pipe->next = NULL;
}

int	init_pipes(t_cmd_list *cmd_list, t_all *all)
{
	t_pipe	*tmp_pipe;

	all->pipes = malloc(sizeof(t_pipe));
	if (!all->pipes)
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

void	mini_loop(t_all *all, t_sl_list *env)
{
	char			*line;
	t_cmd_list		*cmd_list;

	while (1)
	{
		line = readline("");
		add_history(line);
		cmd_list = parse_input(line);
		if (print_error())
			continue ;
		init_pipes(cmd_list, all);
		if (print_error())
			continue ;
		start_executor(all);
		if (print_error())
			continue ;
		// free_line_and_pipe(all, line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_all			*all;
	t_sl_list		*env_var;

	(void) argc;
	(void) argv;
	init_signals();
	all = malloc(sizeof(t_all));
	if (!all)
		return (ft_puterror("allocation error"));
	env_var = get_env_var(envp);
	init_all(all, envp);

	// free_all_and_env(all);
	return (0);
}

int	err_print(char *msg)
{
	printf("%s", msg);
	err_code = 0;
	return (1);
}
int	print_error(void)
{
	if (!err_code)
		return (0);
	else if (err_code == 2)
		return (err_printf(ERR_INIT_PARAM));
}
