/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_chunk_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 22:33:41 by cdell             #+#    #+#             */
/*   Updated: 2022/09/06 04:22:50 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_str_chunk	*create_new_chunk(size_t length, char *chunk)
{
	t_str_chunk	*node;

	node = NULL;
	node = (t_str_chunk *)malloc(sizeof (t_str_chunk));
	if (!node)
		init_err(MEM_ERR, "", 1, 0);
	node->length = length;
	node->str = chunk;
	return (node);
}

void	clear_str_chunk(void *str_chunk)
{
	t_str_chunk	*chunk;

	chunk = (t_str_chunk *)str_chunk;
	free(chunk->str);
	free(chunk);
	chunk = NULL;
}

void	append_chunk(t_list **token_list, size_t length, char *chunk)
{
	t_str_chunk	*st_chunk_node;
	t_list		*new_node;

	st_chunk_node = create_new_chunk(length, chunk);
	new_node = ft_lstnew((void *)st_chunk_node);
	ft_lstadd_back(token_list, new_node);
}
