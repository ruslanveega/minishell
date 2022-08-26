/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_buildins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 03:26:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/27 01:23:39 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	execute_build(t_pipe *pipe)
{
	if (pipe->command == "echo")
		echo(pipe->line);
	else if (pipe->command == "cd")
		ft_cd(pipe->line, pipe->env);
	else if (pipe->command == "env")
		ft_env(pipe->env, 0);
	else if (pipe->command == "exit")
		ft_exit(pipe);
	else if (pipe->command == "export")
		ft_export(pipe->line, pipe->env);
	else if (pipe->command == "pwd")
		ft_pwd(pipe->env);
	else if (pipe->command == "unset")
		ft_unset(pipe->line, pipe->env);
	else
		return (1);
	return (0);
}
