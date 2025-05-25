# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:15:38 by yaperalt          #+#    #+#              #
#    Updated: 2025/05/25 15:14:49 by jalcausa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC = cc
CFLAGS	= -Wall -Wextra -Werror

LIBFT	= libft
LIBS = $(LIBFT)/libft.a

# Detectar sistema operativo
UNAME := $(shell uname)

# Configuración para macOS
ifeq ($(UNAME), Darwin)
    RL_PATH  = /usr/local/opt/readline
    RL_LIB   = -I $(RL_PATH)/include
    RL_LINK  = -L $(RL_PATH)/lib
else
    # Configuración para Ubuntu
    RL_LIB   = -I /usr/include
    RL_LINK  = -L /usr/lib/x86_64-linux-gnu
endif

HEADERS = -I $(LIBFT) -I ./includes $(RL_LIB)


SRCS	= 	src/main.c							\
			src/shell_loop.c					\
			src/utils/init.c					\
			src/utils/signals.c					\
			src/utils/exit.c					\
			src/utils/free.c					\
			src/utils/expand_variables.c		\
			src/utils/errors.c					\
			src/env/get_env_value.c				\
			src/env/split_env.c					\
			src/parser/lexer/lexer.c			\
			src/parser/lexer/states.c			\
			src/parser/lexer/utils.c			\
			src/parser/parser/parser.c			\
			src/parser/parser/states.c			\
			src/parser/parser/states2.c			\
			src/parser/parser/actions.c			\
			src/parser/parser/actions_heredoc.c	\
			src/parser/parser/utils.c			\
			src/executer/executer.c				\
			src/executer/exec_cd.c				\
			src/executer/exec_echo.c			\
			src/executer/exec_env.c				\
			src/executer/exec_exit.c			\
			src/executer/exec_export.c			\
			src/executer/exec_pwd.c				\
			src/executer/exec_unset.c			\
			src/executer/executer_utils.c		

OBJS	= $(SRCS:.c=.o)

all: libft $(NAME)

libft:	
	make -C $(LIBFT)

%.o: %.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT)/libft.a -lreadline $(RL_LINK) $(HEADERS) -o $(NAME) 

clean:
	rm -rf $(OBJS)
	make clean -C $(LIBFT)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBFT)/libft.a

re: fclean all

.PHONY: all clean fclean re libft