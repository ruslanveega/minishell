/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 21:30:15 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 16:58:32 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_redirect(int key)
{
	if (
		key == REDIRECT_IN || key == REDIRECT_OUT
		|| key == REDIRECT_APPEND || key == REDIRECT_HEREDOC)
		return (1);
	return (0);
}
