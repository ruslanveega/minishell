/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:25 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/18 23:43:49 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_sl_list *env, int declare)
{
	if (env == NULL)
		env_error();
	while (env != NULL)
	{
		if (env->key)
		{
			if (declare)
				printf("declare -x %s=%s\n", env->key, env->value);
			else
				printf("%s=%s\n", env->key, env->value);
		}
		env = env->next;
	}

}
