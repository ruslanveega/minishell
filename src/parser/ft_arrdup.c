/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:44:37 by cdell             #+#    #+#             */
/*   Updated: 2022/09/09 03:43:48 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int get_charr_size(char *arr[])
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
	int		i;

	line = (char **)malloc(sizeof(char *) * get_charr_size(cmd_options) + 1);
	if (!line)
		init_err(MEM_ERR, NULL, 1, 12);
	i = 0;
	while (cmd_options[i]) {
		line[i] = ft_strdup(cmd_options[i]);
		if (!line[i])
			init_err(MEM_ERR, NULL, 1, 12);
		i++;
	}
	line[i] = NULL;
	return (line);
}
