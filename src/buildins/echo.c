/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:28 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/11 19:19:02 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(char **line)
{
	int	put_n;
	int	num;

	put_n = 1;
	num = 0;
	while (line[num])
		num++;
	if (num < 2)
		return (1);
	num = 1;
	while (line[num])
	{
		if (ft_strcmp(line[num], "-n") == 0)
		{
			put_n = 0;
			num++;
		}
		ft_putstr_fd(line[num], 1);
		if (line[num][0] != '\0')
			write(1, " ", 1);
		num++;
	}
	if (put_n)
		write(1, "\n", 1);
	return (1);
}
