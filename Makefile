# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/09 15:15:38 by yaperalt          #+#    #+#              #
#    Updated: 2025/06/10 17:20:39 by yaperalt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# ANSI color codes
GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

# Variables
NAME	= minishell
CC = cc
CFLAGS	= -Wall -Wextra -Werror -g

LIBFT	= libft
LIBS = $(LIBFT)/libft.a

# Detect OS
UNAME := $(shell uname)

# MacOS
ifeq ($(UNAME), Darwin)
    RL_PATH  = /opt/homebrew/opt/readline
    RL_LIB   = -I $(RL_PATH)/include
    RL_LINK  = -L $(RL_PATH)/lib
else
    # Ubuntu
    RL_LIB   = -I /usr/include
    RL_LINK  = -L /usr/lib/x86_64-linux-gnu
endif

HEADERS = -I $(LIBFT) -I ./includes $(RL_LIB)


SRCS	= 	src/main.c							\
            src/shell_loop.c					\
            src/utils/init.c					\
            src/utils/signals.c					\
			src/utils/signals2.c				\
            src/utils/exit.c					\
            src/utils/free.c					\
            src/utils/expand_variables.c		\
            src/utils/errors.c					\
            src/utils/pipes.c					\
            src/env/get_env_value.c				\
            src/env/split_env.c					\
            src/env/set_export_env_var.c		\
            src/env/parse_env.c					\
            src/env/remove_env_var.c			\
            src/env/remove_exportenv_var.c		\
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
            src/executer/executer_utils.c		\
			src/executer/exec_cd2.c

OBJS	= $(SRCS:.c=.o)

all: libft $(NAME)

libft:
	make -C $(LIBFT)

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $@$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT)/libft.a -lreadline $(RL_LINK) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Compilation complete, executable created!$(RESET)"

clean:
	@rm -rf $(OBJS)
	@make clean -C $(LIBFT)
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@echo "$(YELLOW)Cleaning libft...$(RESET)"
	@echo "$(GREEN)Basic clean complete, executable remaining!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)/libft.a
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft
