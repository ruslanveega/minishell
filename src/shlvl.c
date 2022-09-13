/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:39:22 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/12 21:00:13 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	incr_shlvl(t_all *g_all, int incr)
{
	t_sl_list	*env;

	env = g_all->env;
	while (env)
	{
		if (ft_strcmp(env->key, "SHLVL") == 0)
		{
			free(env->value);
			env->value = ft_itoa(ft_atoi(env->value) + incr);
			break ;
		}
		env = env->next;
	}
}
