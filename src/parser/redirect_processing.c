/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:39:22 by cdell             #+#    #+#             */
/*   Updated: 2022/09/10 22:59:11 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redirect	*create_new_redirect(int type, char *file)
{
	t_redirect	*node;

	node = NULL;
	node = (t_redirect *)malloc(sizeof (t_redirect));
	if (!node)
		init_err(MEM_ERR, "", 1, 0);
	node->type = type;
	node->file = file;
	return (node);
}

void	clear_redirect(void *redirect)
{
	t_redirect	*node;

	if (redirect == NULL)
		return ;
	node = (t_redirect *)redirect;
	free(node->file);
	free(node);
	redirect = NULL;
}

void	append_redirect(t_list **redirect_list, int type, char *value)
{
	t_redirect	*redirect;
	t_list		*new_node;

	redirect = create_new_redirect(type, value);
	new_node = ft_lstnew((void *)redirect);
	if (!new_node)
		init_err(MEM_ERR, "", 1, 0);
	ft_lstadd_back(redirect_list, new_node);
}
