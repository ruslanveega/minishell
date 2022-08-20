/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:02:02 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 16:58:00 by cdell            ###   ########.fr       */
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
	exit_status = get_exit_status_code();
	chunk = ft_itoa(exit_status);
	if (chunk)
	{
		length = ft_strlen(chunk);
		append_chunk(db_quote_chunk, length, chunk);
	}
}

int	get_exit_status_code(void)
{
	return (0);
}
