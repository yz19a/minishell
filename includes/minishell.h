/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:07:21 by jalcausa          #+#    #+#             */
/*   Updated: 2025/04/21 17:56:43 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdlib.h>

// Estructuras:

typedef struct s_command
{
	char	**argv;
	int		argc;
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_shell_data
{
	char		**env;
	int			dup_stdin;
	int			dup_stdout;
	t_list		*commands;
	char		**exportenv;
}	t_shell_data;

typedef struct s_global_sig
{
	int		exit_status;
	pid_t	pid;
}	t_global_sig;

// Prototipos de funciones:

// Inicializar datos (init.c):

t_shell_data	*init_shell_data(char **env);
void			sig_init(void);

// Manejo de señales (signals.c)
void	set_signals_interactive(void);
void	ignore_sigquit(void);
void	signal_reset_prompt(int signal);
void	print_newline(int signal);
void	set_signals_noninteractive(void);

// Bucle principal (shell_loop.c)
void	shell_loop(t_shell_data *data);

// free.c
void	free_ptr(void *ptr);
void	free_envs(t_shell_data *data);
void	del_t_command(void *com);

//exit.c
void	exit_shell(t_shell_data *data, int exitcode);

extern t_global_sig	g_sig;

#endif