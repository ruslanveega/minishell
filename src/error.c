/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 03:57:39 by fcassand          #+#    #+#             */
/*   Updated: 2022/08/19 04:27:07 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(void)
{
	if (!err_str->code)
		return (0);
	else
	{
		printf("minishell$ %s: %s", err_str->code, err_str->token);
		err_str->code = NULL;
		err_str->token = NULL;
		if (err_str->exit)
		{
			err_str->exit = 0;
			exit(EXIT_FAILURE);
		}
		return (1);
	}
}
