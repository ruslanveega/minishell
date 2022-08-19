/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:39:22 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/19 03:57:04 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incr_shlvl(t_all *all, int incr)
{
	t_sl_list	*env;

	env = all->env;
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			env->value = ft_itoa(ft_atoi(env->value) + incr);
			break ;
		}
		env = env->next;
	}
}
