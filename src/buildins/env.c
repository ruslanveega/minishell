/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:25 by fcassand          #+#    #+#             */
/*   Updated: 2022/07/18 19:17:25 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(t_sl_list *env)
{
	t_sl_list	*tmp_env;

	tmp_env = env;
	while (tmp_env != NULL)
	{
		if (tmp_env->key != NULL)
			printf("%s=%s\n", tmp_env->key, tmp_env->value);
		tmp_env = tmp_env->next;
	}
	if (env == NULL)
		env_error();
}
