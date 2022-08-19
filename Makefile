NAME	=	minishell

LIBFT_DIR	=	libft/

LIBFT_A		=	${LIBFT_DIR}libft.a

SRCS	=	src/main.c\
			src/utils/ft_puterror.c\
			src/utils/list_ops.c\
			src/utils/ft_substr_len.c\
			src/lexer/token_list_handler.c\
			src/env_var/env_var.c\
			src/env_var/env_var_list_handler.c\
			src/lexer/lexer.c\
			src/lexer/print_list.c\
			src/lexer/token_utlis.c\
			src/lexer/token_value_utils.c\
			src/parser/parser.c\
			src/parser/env_var_expansion.c\
			src/parser/db_quotes_expansion.c\
			src/parser/join_tokens.c\
			src/parser/exit_status.c\
			src/parser/token_list_eval.c\
            src/parser/token_list_expansion.c\
            src/parser/strip_spaces.c\
            src/parser/is_redirect.c\
			src/parser/redirect_processing.c\
			src/parser/cmd_list_handler.c\
			src/parser/str_chunk_handler.c\
			src/parser/cmd_processing.c\
			src/parser/clear_array.c\
			src/parser/token_key_getter.c\
			src/parser/print_functions.c\
			src/buildins/cd.c\
			src/buildins/echo.c\
			src/buildins/env.c\
			src/buildins/exit.c\
			src/buildins/export.c\
			src/buildins/pwd.c\
			src/buildins/unset.c\
			src/executor/exec_buildins.c\
			src/executor/exec_utils.c\
			src/executor/executor.c\
			src/executor/pipe_execution.c\
			src/signals.c



HEADER	=	src/minishell.h

OBJS	=	$(SRCS:.c=.o)

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror

.PHONY	:	all clean fclean re libft

all		:	$(LIBFT_A) $(NAME)

$(LIBFT_A)	:	libft ;

libft	:
	make -C $(LIBFT_DIR)

$(NAME)	:	$(LIBFT_A) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) -lreadline -o $(NAME)

%.o		:	%.c	$(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean	:
	make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)

fclean	:	clean
	make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re	:	fclean all
