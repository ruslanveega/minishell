/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 17:35:32 by cdell             #+#    #+#             */
/*   Updated: 2021/10/25 17:49:00 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_item;
	t_list	*list_start;
	void	*content;

	if (!lst)
		return (NULL);
	list_start = NULL;
	while (lst)
	{
		content = (*f)(lst->content);
		new_item = ft_lstnew(content);
		if (!new_item)
		{
			ft_lstclear(&list_start, del);
			return (NULL);
		}
		ft_lstadd_back(&list_start, new_item);
		lst = lst->next;
	}
	return (list_start);
}
