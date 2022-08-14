/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 21:42:02 by cdell             #+#    #+#             */
/*   Updated: 2022/08/07 04:09:49 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_puterror(char *msg)
{
	write(2, "\e[1;31mERROR:\e[0m\n", 19);
	perror(msg);
	exit(EXIT_FAILURE);
	return (1);
}

//int	exception(const char *message, const char *error_line, int code)
//{
//	if (error_line)
//	{
//		write(2, DEF_COLOR, 7);
//		write(2, error_line, ft_strlen(error_line));
//		write(2, "\n", 1);
//		write(2, NO_COLOR, 4);
//	}
//	if (message)
//	{
//		write(2, "Error: ", 7);
//		write(2, message, ft_strlen(message));
//		write(2, "\n", 1);
//	}
//	if (!code)
//		return (0);
//	exit(code);
//}
