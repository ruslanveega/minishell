/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:14:51 by cdell             #+#    #+#             */
/*   Updated: 2022/07/21 05:21:53 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_token t_token;

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "lexer/lexer.h"

typedef struct s_sl_list
{
	void	*key;
	void	*value;
	struct s_sl_list	*next;
}	t_sl_list;

void	lst_append_node(t_sl_list **list, void *key, void *value);
t_sl_list	*get_env_var(char *env[]);

t_sl_list	*get_token_list(void);

void	ft_puterror(char *msg);
int		ft_strcmp(const char *s1, const char *s2);
int		num_args(char **line);

#endif //MINISHELL_H
