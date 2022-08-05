/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:14:51 by cdell             #+#    #+#             */
/*   Updated: 2022/08/04 00:17:02 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

typedef struct s_redir
{
	int		type;
	char	*file;
	t_redir	*next;
}	t_redir;

typedef struct s_pipe
{
	t_sl_list	*env;
	t_redir		*redir;
	char		*command;
	int			is_add_new_var;
	char		**line;
	int			result;
	char		*error;
	t_pipe		*next;
}	t_pipe;

typedef struct s_all
{
	// int			exit;
	int			exit_status;
	t_sl_list	*env;
	t_pipe		*pipes;
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
