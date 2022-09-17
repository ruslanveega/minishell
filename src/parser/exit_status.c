/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:02:02 by cdell             #+#    #+#             */
/*   Updated: 2022/09/17 06:32:07 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	handle_exit_status(t_list **db_quote_chunk, char **str)
{
	char	*chunk;
	int		exit_status;
	size_t	length;

	(*str) += 2;
	chunk = NULL;
	exit_status = g_all->err_str->exit_status;
	chunk = ft_itoa(exit_status);
	if (chunk)
	{
		length = ft_strlen(chunk);
		append_chunk(db_quote_chunk, length, chunk);
	}
}
