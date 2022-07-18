/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:17 by fcassand          #+#    #+#             */
/*   Updated: 2022/07/18 18:59:05 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_sl_list *env)
{
	t_sl_list	*tmp;

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
}
