/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:44:37 by cdell             #+#    #+#             */
/*   Updated: 2022/09/03 21:06:01 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int get_arr_size(char *arr[])
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	**ft_arrdup(char *cmd_options[])
{
	char	**line;
	char	*str;
	int		i;

	line = (char **)malloc(sizeof(char *) * get_arr_size(cmd_options) + 1);
	if (!line)
		init_err(MEM_ERR, NULL, 1, 12);
	i = 0;
	while (cmd_options[i]) {
		str = ft_strdup(cmd_options[i]);
		if (!str)
			init_err(MEM_ERR, NULL, 1, 12);
		line[i++] = str;
	}
	line[i] = NULL;
	return (line);
}
