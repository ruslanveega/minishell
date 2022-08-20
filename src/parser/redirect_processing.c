/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:39:22 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 17:36:59 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_redirect	*create_new_redirect(int type, char *file)
{
	t_redirect	*node;

	node = NULL;
	node = (t_redirect *)malloc(sizeof (t_redirect));
	if (!node)
		ft_puterror("Failed to allocate memory for redirect in\
		 redirect_processing.c->create_new_redirect");
	node->type = type;
	node->file = file;
	return (node);
}

void	append_redirect(t_list **redirect_list, int type, char *value)
{
	t_redirect	*redirect;
	t_list		*new_node;

	redirect = create_new_redirect(type, value);
	new_node = ft_lstnew((void *)redirect);
	if (!new_node)
		ft_puterror("Could not allocate memory in parser.c->get_cmd_list");
	ft_lstadd_back(redirect_list, new_node);
}
