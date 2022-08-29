/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 06:50:35 by cdell             #+#    #+#             */
/*   Updated: 2022/08/30 02:33:04 by fcassand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../minishell.h"

# define NEWLINE_STR "\'newline\'"
# define PIPE_STR "\'|\'"
# define REDIRECT_IN_STR "\'<\'"
# define REDIRECT_OUT_STR "\'>\'"
# define REDIRECT_APPEND_STR "\'>>\'"
# define REDIRECT_HEREDOC_STR "\'<<\'"

typedef enum s_result
{
	ERROR = 0,
	SUCCESS = 1
}	t_result;

typedef struct s_redirect
{
	int		type;
	char	*file;
}	t_redirect;

typedef struct s_redir
{
	int				type;
	char			*file;
	struct s_redir	*next;
}	t_redir;

typedef struct s_str_chunk
{
	size_t	length;
	char	*str;
}	t_str_chunk;

typedef struct s_cmd_list
{
	char				**cmd_options;
	t_redir				*redirect;
	struct s_cmd_list	*next;
}	t_cmd_list;

// Token utils
int			get_token_node_key(t_list *token_list);

// Token list expansion
void		expand_token_list(t_list *token_list);
char		*substitute_env_var_val(const char *start, const char *end);
void		*lookup_env_var_val(const char *start, const char *end);
char		*get_str_from_db_quotes(char *db_quotes_str);
int			get_exit_status_code(void);
void		handle_exit_status(t_list **db_quote_chunk, char **str);

// String chunk list
void		append_chunk(t_list **token_list, size_t length, char *chunk);
void		clear_str_chunk(void *str_chunk);

// Strip white spaces
//void	strip_space(t_sl_list *token_list);
void		strip_space(t_list *token_list);

// Join tokens
//int		should_join(size_t key);
int			should_join(int key);
void		join_token_list(t_list *token_list);

// Token list evaluation
//void		evaluate_token_list(t_list *token_list);
int			evaluate_token_list(t_list *token_list);

// Process redirections
// void		append_redirect(t_list **redirect_list, int type, char *value);
// t_redirect	*process_redirect(t_list *token_list);
// //t_redirect	*get_redirect(t_list *token_list);

// Process commands
void		get_cmd_list(t_cmd_list **cmd_list, t_list *token_list);
void		append_cmd(t_cmd_list **cmd_list, t_redir *redirect,
				char *cmd_options[]);

// Clear command list
void		*clear_array(char **arr);

// Printing
void		print_cmd_list(t_cmd_list *cmd_list);
void		print_redirect_list(t_list *list);
void		print_options(char *str[]);

#endif // PARSER_H
