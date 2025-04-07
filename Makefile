# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:15:38 by yaperalt          #+#    #+#              #
#    Updated: 2025/04/07 23:17:02 by jalcausa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
CFLAGS	= -Wall -Wextra -g -Werror
LIBFT	= libft
RL_PATH  = /usr/local/opt/readline
RL_LIB   = -I $(RL_PATH)/include
RL_LINK  = -L $(RL_PATH)/lib
HEADERS = -I $(LIBFT) -I ./includes $(RL_LIB)
LIBS = $(LIBFT)/libft.a
CC = gcc
SRCS	= 	src/loop_shell.c \
			src/minishell.c

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