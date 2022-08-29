/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 21:49:22 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 02:07:12 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	*lookup_env_var_val(const char *start, const char *end)
{
	t_sl_list	*env_var_list;
	size_t		length;
	char		*str;

	env_var_list = all->env;
	str = NULL;
	length = ft_substr_len(start, end);
	while (env_var_list)
	{
		if (strncmp(start, env_var_list->key, length) == 0)
		{
			str = ft_strdup(env_var_list->value);
			break ;
		}
		env_var_list = env_var_list->value;
	}
	return (str);
}

// void	*lookup_env_var_val(const char *start, const char *end)
// {
// 	t_list		*env_var_list;
// 	t_env_var	*env_var_node;
// 	size_t		length;
// 	char		*str;

// 	env_var_list = all->env;
// 	str = NULL;
// 	length = ft_substr_len(start, end);
// 	while (env_var_list)
// 	{
// 		env_var_node = (t_env_var *)env_var_list->content;
// 		if (strncmp(start, env_var_node->key, length) == 0)
// 		{
// 			str = ft_strdup(env_var_node->value);
// 			break ;
// 		}
// 		env_var_list = env_var_list->next;
// 	}
// 	return (str);
// }

char	*substitute_env_var_val(const char *start, const char *end)
{
	char	*str;

	str = lookup_env_var_val(start, end);
	return (str);
}
