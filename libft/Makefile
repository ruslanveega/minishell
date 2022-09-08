# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcassand <fcassand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 04:14:52 by cdell             #+#    #+#              #
#    Updated: 2022/09/07 01:36:21 by fcassand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libft.a

SRCS	=	ft_memchr.c		ft_strdup.c		ft_substr.c\
			ft_memcmp.c		ft_striteri.c	ft_tolower.c\
			ft_atoi.c		ft_memcpy.c		ft_strjoin.c\
			ft_toupper.c	ft_bzero.c		ft_memmove.c\
			ft_strlcat.c	ft_calloc.c		ft_memset.c\
			ft_strlcpy.c	ft_isalnum.c	ft_putchar_fd.c\
			ft_strlen.c		ft_isalpha.c	ft_putendl_fd.c\
			ft_strmapi.c	ft_isascii.c	ft_putnbr_fd.c\
			ft_strncmp.c	ft_isdigit.c	ft_putstr_fd.c\
			ft_strnstr.c	ft_isprint.c	ft_split.c\
			ft_strrchr.c	ft_itoa.c		ft_strchr.c\
			ft_strtrim.c\
			ft_lstnew.c		ft_lstadd_front.c	ft_lstsize.c\
			ft_lstlast.c	ft_lstadd_back.c	ft_lstdelone.c\
			ft_lstclear.c	ft_lstiter.c		ft_lstmap.c\

HEADER	=	libft.h

OBJ		=	$(SRCS:.c=.o)
OBJ_B	=	$(SRCS_B:.c=.o)

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-I$(HEADER)

.PHONY	:	all clean fclean re bonus

all		:	$(NAME)

$(NAME)	:	$(OBJ) $(HEADER)
	ar rcs $(NAME) $?

%.o		:	%.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

bonus	:
	@make OBJ='$(OBJ_B)' all

clean	:
	@$(RM) $(OBJ) $(OBJ_B)

fclean	:	clean
	@$(RM) $(NAME)

re		:	fclean all
