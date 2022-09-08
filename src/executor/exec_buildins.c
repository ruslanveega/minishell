/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:26:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/08 04:12:00 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_build(t_pipe *pipe)
{
	if (!ft_strcmp(pipe->command, "echo"))
		echo(pipe->line);
	else if (!ft_strcmp(pipe->command, "cd"))
		ft_cd(pipe->line, g_all->env);
	else if (!ft_strcmp(pipe->command, "env"))
		ft_env(g_all->env, 0);
	else if (!ft_strcmp(pipe->command, "exit"))
		ft_exit(pipe);
	else if (!ft_strcmp(pipe->command, "export"))
		ft_export(pipe->line, g_all->env);
	else if (!ft_strcmp(pipe->command, "pwd"))
		ft_pwd(g_all->env);
	else if (!ft_strcmp(pipe->command, "unset"))
		ft_unset(pipe->line, g_all->env);
	else
		return (1);
	return (0);
}
