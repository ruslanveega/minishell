/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:57:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/30 02:37:34 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_redirs(t_redir *redir)
{
	t_redir	*tmp_redir;

	while (redir)
	{
		tmp_redir = redir->next;
		if (redir->file)
			free(redir->file);
		free(redir);
		redir = tmp_redir;
	}
}

void	free_pipe_cmd(t_pipe *pipes, t_cmd_list *cmd_list)
{
	t_pipe		*tmp_pipe;
	t_cmd_list	*tmp_cmd;
	int			i;

	i = 0;
	while (cmd_list)
	{
		tmp_cmd = cmd_list->next;
		while (cmd_list->cmd_options[i])
			free(cmd_list->cmd_options[i++]);
		free(cmd_list->cmd_options);
		free_redirs(cmd_list->redirect);
		free (cmd_list);
		cmd_list = tmp_cmd;
	}
	while (pipes)
	{
		tmp_pipe = pipes->next;
		free(pipes);
		pipes = tmp_pipe;
	}
	cmd_list = NULL;
	pipes = NULL;
}

void	free_all_and_env(t_all *all)
{
	t_sl_list	*tmp_env;

	if (all->pipes)
		free_pipe_cmd(all->pipes, NULL);
	if (all->env)
	{
		while (all->env)
		{
			tmp_env = all->env->next;
			if (all->env->key)
				free(all->env->key);
			if (all->env->value)
				free(all->env->value);
			free(all->env);
			all->env = tmp_env;
		}
	}
	all->pipes = NULL;
	all->env = NULL;
	free(all);
}

int	init_err(char *code, char *token, int exit, int exit_status)
{
	if (code)
		all->err_str->code = code;
	if (token)
		all->err_str->token = token;
	if (exit)
		print_error();
	if (exit_status)
		all->err_str->exit_status = exit_status;
	return (1);
}

int	print_error(void)
{
	if (!all->err_str->code)
	{
		all->err_str->exit_status = 0;
		return (0);
	}
	else
	{
		printf("minishell$ %s: %s", all->err_str->token, all->err_str->code);
		all->err_str->code = NULL;
		all->err_str->token = NULL;
		if (all->err_str->exit)
		{
			all->err_str->exit = 0;
			exit(EXIT_FAILURE);
		}
		return (1);
	}
}
