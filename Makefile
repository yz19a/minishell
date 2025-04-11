# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:15:38 by yaperalt          #+#    #+#              #
#    Updated: 2025/04/11 18:55:13 by jalcausa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CC = cc
CFLAGS	= -Wall -Wextra -g -Werror

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
    # Configuración para Ubuntu (y otras distribuciones Linux)
    RL_LIB   = -I /usr/include
    RL_LINK  = -L /usr/lib/x86_64-linux-gnu
endif

HEADERS = -I $(LIBFT) -I ./includes $(RL_LIB)


SRCS	= 	src/shell_loop.c	\
			src/minishell.c		\
			src/utils/init.c

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