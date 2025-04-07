/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:07:21 by jalcausa          #+#    #+#             */
/*   Updated: 2025/04/07 23:09:14 by jalcausa         ###   ########.fr       */
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

extern t_global_sig	g_sig;

#endif