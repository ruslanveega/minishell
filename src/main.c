/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 20:01:56 by cdell             #+#    #+#             */
/*   Updated: 2022/09/11 19:17:27 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_pipe_args(t_pipe *pipe, t_cmd_list *cmd)
{
	pipe->redir = get_redir_list(cmd->redirect);
	pipe->command = ft_strdup(cmd->cmd_options[0]);
	pipe->line = ft_arrdup(cmd->cmd_options);
	pipe->heredoc = NULL;
	pipe->next = NULL;
}

void	init_pipes(t_cmd_list *cmd_list, t_all *g_all)
{
	t_pipe		*tmp_pipe;
	t_cmd_list	*tmp_cmd;

	tmp_cmd = cmd_list;
	g_all->pipes = malloc(sizeof(t_pipe));
	if (!g_all->pipes)
		g_all->err_str->code = MEM_ERR;
	tmp_pipe = g_all->pipes;
	while (cmd_list)
	{
		make_pipe_args(g_all->pipes, cmd_list);
		if (cmd_list->next)
		{
			g_all->pipes->next = malloc(sizeof(t_pipe));
			if (!g_all->pipes->next)
				init_err(MEM_ERR, "", 1, 0);
			g_all->pipes = g_all->pipes->next;
			cmd_list = cmd_list->next;
		}
		else
			break ;
	}
	clear_cmd_list(tmp_cmd);
	g_all->pipes = tmp_pipe;
}

void	mini_loop(t_all *g_all)
{
	char			*line;
	t_cmd_list		*cmd_list;

	cmd_list = NULL;
	while (1)
	{
		free_pipe_cmd(g_all->pipes);
		if ((g_all->err_str->code
				&& !ft_strcmp(g_all->err_str->code, MEM_ERR))
			|| g_all->err_str->exit)
			break ;
		line = readline("minishell$ ");
		add_history(line);
		cmd_list = parse_input(line);
		if (print_error() || cmd_list == NULL)
			continue ;
		init_pipes(cmd_list, g_all);
		start_executor(g_all);
		if (print_error())
			continue ;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	init_signals();
	g_all = malloc(sizeof(t_all));
	if (!g_all)
		g_all->err_str->code = MEM_ERR;
	g_all->env = get_env_var(envp);
	g_all->pipes = NULL;
	g_all->err_str = malloc(sizeof(t_error));
	if (!g_all->err_str)
	{
		return (1);
		free_all_and_env(g_all);
	}
	g_all->err_str->code = NULL;
	g_all->err_str->exit = 0;
	g_all->err_str->token = NULL;
	g_all->err_str->exit_status = 0;
	incr_shlvl(g_all, 1);
	mini_loop(g_all);
	free_all_and_env(g_all);
	return (0);
}
