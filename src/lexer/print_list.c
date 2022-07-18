#include "lexer.h"

static void print_token(t_sl_list *token_ls)
{
	if (token_ls->key == (void *)SPACE)
		printf("token = space\n");
	else if (token_ls->key == (void *)WORD)
		printf("token = word\tvalue = %s\n", (char *)token_ls->value);
	else if (token_ls->key ==(void *) ENV_VAR)
		printf("token = ENV_VAR\t value = %s\n", (char *)token_ls->value);
	else if (token_ls->key == (void *)SINGLE_QUOTE)
		printf("token = SINGLE quote\tvalue = %s\n", (char *)token_ls->value);
	else if (token_ls->key == (void *)DOUBLE_QUOTE)
		printf("token = DOUBLE quote\tvalue = %s\n", (char *)token_ls->value);
	else if (token_ls->key == (void *)REDIRECT_IN)
		printf("token = <\tvalue Redirection in\n");
	else if (token_ls->key == (void *)REDIRECT_OUT)
		printf("token = >\tvalue = Redirection out\n");
	else if (token_ls->key == (void *)REDIRECT_APPEND)
		printf("token = >> (APPEND)\n");
	else if (token_ls->key == (void *)REDIRECT_HEREDOC)
		printf("token = << (HEREDOC)\n");
	else if (token_ls->key == (void *)PIPE)
		printf("token = |\t value = Pipe\n");
//			// Bonus
//		IF_AND_TK = 11,
//		IF_OR_TK = 12,
//		OPEN_PARAN_TK = 13,
//		CLOSE_PARAN_TK = 14,
//		UNKOWN_TOKEN_TK = 15)
}

void	print_list(t_sl_list *token_ls)
{
	if (!token_ls)
	{
		printf("Token list is empty\n");
		exit(EXIT_FAILURE);
	}
	while (token_ls)
	{
		print_token(token_ls);
		token_ls = token_ls->next;
	}
}
