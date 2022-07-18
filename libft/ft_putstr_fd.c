/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 00:58:37 by cdell             #+#    #+#             */
/*   Updated: 2021/10/21 06:04:03 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str);

void	ft_putstr_fd(char *s, int fd)
{
	if (fd != -1 && s)
	{
		write(fd, s, ft_strlen(s));
	}
}
