/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_len.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 18:37:33 by cdell             #+#    #+#             */
/*   Updated: 2022/08/03 18:37:35 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_substr_len(const char *start, const char *end)
{
	size_t length;

	length = 0;
	if (!end)
		return (ft_strlen(start));
	while (start < end)
	{
		length++;
		start++;
	}
	return (length);
}
