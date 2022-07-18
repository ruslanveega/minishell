NAME	=	minishell

LIBFT_DIR	=	libft/

LIBFT_A		=	${LIBFT_DIR}libft.a

SRCS	=	src/main.c src/ft_puterror.c\
			src/lexer/lexer.c src/lexer/lst_token_ops.c\
			src/lexer/print_list.c	src/lexer/token_utlis.c\
			src/list_ops.c	src/env_var.c

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