/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_prototypes.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:15:49 by yaperalt          #+#    #+#             */
/*   Updated: 2025/03/23 15:44:34 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PROTOTYPES_H
# define MINISHELL_PROTOTYPES_H

# include "../libft/libft.h"
# include "minishell_structures.h"
// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <readline/readline.h>
# include <readline/history.h>
// printf, perror
# include <stdio.h>
// malloc, free, exit, getenv
# include <stdlib.h>
// write, access, open, read, close, unlink, fork, execve, dup, dup2, pipe, getcwd, chdir, isatty, ttyname, ttyslot
# include <unistd.h>
// wait, waitpid, wait3, wait4
# include <sys/wait.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <signal.h>
// stat, lstat, fstat
# include <sys/stat.h>
// opendir, readdir, closedir
# include <dirent.h>
// strerror
# include <string.h>
// tcsetattr, tcgetattr
# include <termios.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <curses.h>  // or <termcap.h>
// ioctl
# include <sys/ioctl.h>

t_signals	g_signals;

// handle_signals.c
void handle_ctrl_c(int sig_num);


#endif
