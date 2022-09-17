/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 23:19:28 by fcassand          #+#    #+#             */
/*   Updated: 2022/09/17 06:43:25 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char **line)
{
	int	put_n;
	int	num;

	put_n = 1;
	num = 0;
	while (line[num])
		num++;
	if (num < 2)
		return ;
	num = 1;
	if (ft_strcmp(line[num], "-n") == 0)
	{
		put_n = 0;
		num++;
	}
	while (line[num])
	{
		ft_putstr_fd(line[num], 1);
		if (line[num][0] != '\0')
			write(1, " ", 1);
		num++;
	}
	if (put_n)
		write(1, "\n", 1);
	g_all->err_str->exit_status = 0;
}
