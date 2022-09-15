/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:57:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/15 05:43:13 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp_redir;

	while (redir)
	{
		tmp_redir = redir;
		redir = redir->next;
		if (tmp_redir->file)
			free(tmp_redir->file);
		free(tmp_redir);
	}
}

void	free_pipe_cmd(t_pipe *pipes)
{
	t_pipe		*tmp_pipe;
	int			i;

	while (pipes)
	{
		i = 0;
		tmp_pipe = pipes->next;
		if (pipes->redir)
			free_redirs(pipes->redir);
		if (pipes->heredoc)
			free(pipes->heredoc);
		while (pipes->line[i])
			free(pipes->line[i++]);
		if (pipes->line)
			free(pipes->line);
		pipes->line = NULL;
		if (pipes->command)
			free(pipes->command);
		pipes->command = NULL;
		free(pipes);
		pipes = tmp_pipe;
	}
	g_all->pipes = NULL;
}

void	free_all_and_env(t_all *g_all)
{
	t_sl_list	*tmp_env;

	if (g_all->pipes)
		free_pipe_cmd(g_all->pipes);
	if (g_all->env)
	{
		while (g_all->env)
		{
			tmp_env = g_all->env->next;
			if (g_all->env->key)
				free(g_all->env->key);
			if (g_all->env->value)
				free(g_all->env->value);
			free(g_all->env);
			g_all->env = tmp_env;
		}
	}
	g_all->pipes = NULL;
	g_all->env = NULL;
	free(g_all);
}

int	init_err(char *code, char *token, int exit, int exit_status)
{
	if (code)
		g_all->err_str->code = code;
	if (token)
		g_all->err_str->token = token;
	if (exit)
	{
		g_all->err_str->exit = 1;
		print_error();
	}
	if (exit_status)
		g_all->err_str->exit_status = exit_status;
	return (1);
}

int	print_error(void)
{
	if (!g_all->err_str->code)
	{
		g_all->err_str->exit_status = 0;
		return (0);
	}
	else
	{
		printf("%s: %s \n",
			g_all->err_str->code, g_all->err_str->token);
		g_all->err_str->code = NULL;
		g_all->err_str->token = NULL;
		if (g_all->err_str->exit)
			exit(EXIT_FAILURE);
		return (1);
	}
}
