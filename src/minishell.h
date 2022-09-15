/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 23:14:51 by cdell             #+#    #+#             */
/*   Updated: 2022/09/15 15:19:40 by fcassand         ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "lexer/lexer.h"
# include "parser/parser.h"

# define FALSE 0
# define TRUE 1

# define ERR_INIT_PARAM "syntax error near unexpected token"
# define INVALID_ARG_FOR_UNSET "not a valid identifier"
# define NOT_SET "not set"
# define ERR_CMD_NOT_FOUND "command not found"
# define MEM_ERR "memory allocation error"
# define SYN_ERR "syntax error near unexpected token"
# define TO_MANY "to many arguments"
# define NUM_ARG "numeric argument required"
# define NOT_FILE "No such file or directory"
# define PERM "Permission denied"
# define DUP "can't duplicate descriptor"

typedef struct s_cmd_list	t_cmd_list;

typedef struct s_sl_list
{
	void				*key;
	void				*value;
	struct s_sl_list	*next;
}	t_sl_list;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_error
{
	char	*code;
	char	*token;
	int		exit;
	int		exit_status;
}	t_error;

typedef struct s_env_var
{
	char	*key;
	char	*value;
}	t_env_var;

typedef struct s_pipe
{
	t_redir				*redir;
	char				*command;
	int					fd_in;
	int					fd_out;
	char				**line;
	char				*heredoc;
	struct s_pipe		*next;
}	t_pipe;

typedef struct s_all
{
	t_error		*err_str;
	t_sl_list	*env;
	t_pipe		*pipes;
	pid_t		*pids;
}	t_all;

t_all						*g_all;

//CDELL
// Utils
int			ft_puterror(char *msg);
size_t		ft_substr_len(const char *start, const char *end);
int			is_redirect(int key);

// Singly linked list operations
void		lst_append_node(t_sl_list **list, void *key, void *value);
void		lst_clear(t_sl_list **list);

// Env var setup
t_sl_list	*get_env_var(char *env[]);
void		append_env_var(t_list **env_var_list, char *key, char *value);
void		clear_env_var(t_env_var *env_var_node);

// Lexer
t_list		*get_token_list(char *line);
// Parser
void		clear_redirect(void *redirect);
t_cmd_list	*parse_input(char *line);
void		clear_cmd_list(t_cmd_list *list);
t_redir		*get_redir_list(t_list *redirect_list);
char		**ft_arrdup(char *cmd_options[]);
int			get_charr_size(char *arr[]);
//utils
int			ft_strcmp(const char *s1, const char *s2);
int			num_args(char **line);
size_t		ft_substr_len(const char *start, const char *end);
int			is_redirect(int key);
int			print_error(void);
// Singly linked list operations
void		lst_append_node(t_sl_list **list, void *key, void *value);
void		lst_clear(t_sl_list **list);
//buidins
void		ft_cd(char **line, t_sl_list *env);
int			to_home_or_prev_dir(t_sl_list *env, int old_or_home);
char		*env_path(t_sl_list *env, char *key, int num_sym);
int			update_pwd(t_sl_list *env, char *key, char *path, int num_sym);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_exit(t_pipe *pipes);
int			echo(char **line);
void		ft_env(t_sl_list *env, int declare);
void		ft_export(char **line, t_sl_list *env);
t_sl_list	*valid_env(char *line);
void		env_add_back(t_sl_list *env, t_sl_list *new_env);
void		*export_error(char *error, char *line);
void		ft_pwd(t_sl_list *env);
void		ft_unset(char **line, t_sl_list *env);
int			num_args(char **line);
void		del_env(char *key, t_sl_list *env, int len);
void		free_env(t_sl_list *env);
//executor
void		start_executor(t_all *all);
void		execute_single(t_all *all);
void		execute_bin(t_pipe *pipe);
void		file_execution(t_all *g_all);
char		*get_full_path(char *cmd, t_sl_list *env);
char		**parse_path(t_sl_list *env);
int			ft_to_file(t_redir *redir, int *fd, int flag);
int			read_from_file(t_redir *redir, int *fd);
void		ft_error_exit(char *error, char *cmd);
int			execute_build(t_pipe *pipe);
void		ft_error_exit(char *error, char *cmd);
int			pipe_executor(t_all *all);
int			make_pipes(t_pipe *pipes);
void		choose_out_in(t_pipe *pipes, t_redir *redir);
// void		execute_pipe_bin(t_pipe *pipes, t_all *all);
int			make_heredoc(t_pipe *pipe, t_redir *redir);
void		incr_shlvl(t_all *all, int incr);
char		**env_to_arr(t_sl_list *env);
int			make_heredoc(t_pipe *pipes, t_redir *redir);
//signals
void		init_signals(void);
void		signal_sigint(int sig);
// void		ft_signal_cltr_c(int sig);
int			handler_heredoc(int sig);
int			handler_heredoc2(int sig);
int			handler_heredoc3(int sig);
int			init_err(char *code, char *token, int exit, int exit_status);
int			print_error(void);
void		free_all_and_env(t_all *all);
void		free_pipe_cmd(t_pipe *pipes);
void		free_redirs(t_redir *redir);
void		without_cmd(t_redir *redir, t_cmd_list *tmp_cmd);
#endif
