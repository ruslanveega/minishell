/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:25 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/10 22:54:47 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_sl_list *env, int declare)
{
	if (env == NULL)
		init_err("env: ENV not set", "", 0, 1);
	while (env != NULL)
	{
		if (env->key)
		{
			if (declare)
				printf("declare -x %s=%s\n",
					(char *)env->key, (char *)env->value);
			else
				printf("%s=%s\n", (char *)env->key, (char *)env->value);
		}
		env = env->next;
	}
}
