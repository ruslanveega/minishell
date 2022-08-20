/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:44:24 by cdell             #+#    #+#             */
/*   Updated: 2022/08/19 17:43:28 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"
# define WHITE_SPACE_CHARS " \t\n\v\f\r"
# define TOKENS "'\"<|>()$&"

typedef struct s_sl_list	t_sl_list;

typedef struct s_token
{
	int		key;
	char	*value;
}	t_token;

typedef enum s_token_type
{
	WHITE_SPACE = ' ',
	WORD = 'w',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	ENV_VAR = '$',
	EXIT_STATUS = '?',
	REDIRECT_OUT = '>',
	REDIRECT_IN = '<',
	REDIRECT_APPEND = '+',
	REDIRECT_HEREDOC = '-',
	PIPE = '|',
	IF_AND = '&',
	IF_OR = '_',
	OPEN_PARAN = '(',
	CLOSE_PARAN = ')'
}	t_token_type;

// Token utils
int		get_redirect_token(char **str);
int		get_quote_tk(char **str, char quote_type);
int		get_word_token(char **str);
int		get_space_token(char **str);
int		get_dollar_token(char **str);

// Token value utils
char	*get_word_value(char *start, const char *end);
char	*get_env_var_value(char *start, const char *end);
char	*get_quotes_value(char *start, int type);
char	*get_exit_status(void);

// Token list handler
void	append_token(t_list **token_list, int key, char *value);
void	clear_token(void *token);

// For TESTING purposes only (TO DELETE)
//void	print_list(t_sl_list *token_ls);
void	print_list(t_list *token_ls);

#endif //LEXER_H
