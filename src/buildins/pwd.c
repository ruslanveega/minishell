/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:17 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/17 06:51:52 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_sl_list *env, char **line)
{
	t_sl_list	*tmp;

	if (line[1])
	{
		init_err("pwd", TO_MANY, 0, 1);
	}
	tmp = env;
	while (1)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			ft_putendl_fd(tmp->value, 1);
			return ;
		}
		tmp = tmp->next;
	}
	g_all->err_str->exit_status = 0;
}
