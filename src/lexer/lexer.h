/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdell <cdell@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:44:24 by cdell             #+#    #+#             */
/*   Updated: 2022/06/14 22:44:26 by cdell            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_LEXER_H
# define MINISHELL_LEXER_H

# include "../minishell.h"
# define WHITE_SPACE_CHARS " \t\n\v\f\r"
# define TOKENS "'\"<|>()$&"

typedef struct s_sl_list t_sl_list;

typedef enum s_token_type
{
	WHITE_SPACE = ' ',
	WORD = 'w',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '"',
	ENV_VAR = '$',
	REDIRECT_OUT = '>',
	REDIRECT_IN = '<',
	REDIRECT_APPEND = '+',
	REDIRECT_HEREDOC = '-',
	PIPE = '|',
	// Bonus
	IF_AND = '&',
	IF_OR = '?',
	OPEN_PARAN = '(',
	CLOSE_PARAN = ')'
}	t_token_type;

typedef struct s_token
{
	int 	key;
	char	*value;
	struct s_token	*next;
}	t_token;

typedef	enum e_result_type
{
	ERR,
	OK
}	t_result_type;

typedef struct s_result
{
	t_result_type type;
	void	*value;
}	t_result;

// Token linked list operations
t_token	*lst_new_token(int key, void *value);
void	lst_add_back_token(t_token **token_list, t_token *new_token);
void	lst_add_token(t_token **token_list, int key, void *value);

// Token utils
int		get_redirect_token(char **str);
int		get_quote_tk(char **str, char quote_type);
int		get_word_token(char **str);
int		get_space_token(char **str);

// For TESTING purposes only (TO DELETE)
void	print_list(t_sl_list *token_ls);

#endif //MINISHELL_LEXER_H
