/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:14:51 by cdell             #+#    #+#             */
/*   Updated: 2022/07/24 01:33:48 by fcassand         ###   ########.fr       */
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
	void				*key;
	void				*value;
	struct s_sl_list	*next;
}	t_sl_list;

typedef struct s_all
{
	int			exit;
	int			pipes;
	int			is_buildin;
	t_sl_list	*env;
	t_sl_list	*token;
	t_sl_list	*redir;
	char		**args;
}	t_all;

//parsing
void	lst_append_node(t_sl_list **list, void *key, void *value);
t_sl_list	*get_env_var(char *env[]);
t_sl_list	*get_token_list(char *tmp);

//utils
void	ft_puterror(char *msg);
int		ft_strcmp(const char *s1, const char *s2);
int		num_args(char **line);

//buidins
void	ft_cd(char **line, t_sl_list *env);
int		echo(char **line);
void	ft_env(t_sl_list *env, int declare);
void	ft_export(char **line, t_sl_list *env);
void	ft_pwd(t_sl_list *env);
void	ft_unset(char **line, t_sl_list *env);
//

#endif //MINISHELL_H
