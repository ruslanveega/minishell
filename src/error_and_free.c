/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:57:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/21 00:07:16 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_line_and_pipe(t_all * all, char *line)
{

}

void	free_all_and_env(t_all *all, t_sl_list *env)
{

}

void	init_err(char *code, char *token, int exit, int exit_status)
{
	if (code)
		err_str->code = code;
	if (token)
		err_str->token = token;
	if (exit)
		err_str->exit = exit;
	if (exit_status)
		err_str->exit_status = exit_status;
}

int	print_error(void)
{
	if (!err_str->code)
	{
		err_str->exit_status = 0;
		return (0);
	}
	else
	{
		printf("minishell$ %s: %s", err_str->code, err_str->token);
		err_str->code = NULL;
		err_str->token = NULL;
		if (err_str->exit)
		{
			err_str->exit = 0;
			exit(EXIT_FAILURE);
		};
		return (1);
	}
}
