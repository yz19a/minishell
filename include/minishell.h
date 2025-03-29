/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:15:49 by yaperalt          #+#    #+#             */
/*   Updated: 2025/03/29 17:07:22 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <curses.h>
# include <sys/ioctl.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define TRUNC 3
# define APPEND 4
# define INPUT 5
# define PIPE 6
# define HEREDOC 7
# define END 8

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SKIP 1
# define NOSKIP 0

# define BUFF_SIZE 4096
# define EXPANSION -36
# define SUCCESS 0
# define ERROR 1
# define IS_DIRECTORY 126
# define UNKNOWN_COMMAND 127

# define FALSE 0
# define TRUE 1

extern t_sig g_sig;

/**
 * Structures
 */
typedef struct s_token
{
    char            *str;      // El texto del token (palabra o símbolo)
    int             type;      // El tipo de token (comando, argumento, redirección, etc.)
    struct s_token  *prev;     // Puntero al token anterior
    struct s_token  *next;     // Puntero al token siguiente
}               t_token;

typedef struct s_env
{
    char            *value;     // El valor de la variable (formato "NOMBRE=VALOR")
    struct s_env    *next;      // Puntero a la siguiente variable
}               t_env;

typedef struct s_io_fds
{
    int            dup_in;          // Duplicado del stdin original
    int            dup_out;         // Duplicado del stdout original
    char           *heredoc_file;   // Nombre del archivo temporal para heredoc
    int            fdin;            // Descriptor para entrada
    int            fdout;           // Descriptor para salida
    int            pipin;           // Descriptor para entrada de pipe
    int            pipout;          // Descriptor para salida de pipe
    pid_t          pid;             // ID del proceso
}               t_io_fds;

typedef struct s_ms
{
    t_token         *start;         // Inicio de la lista de tokens
    t_env           *env;           // Lista de variables de entorno
    t_env           *secret_env;    // Variables de entorno ocultas
    t_io_fds        fds;            // Descriptores de archivo
    int             charge;         // Indica si es el proceso principal
    int             parent;         // Indica si es proceso padre
    int             last;           // Indica si es el último comando
    int             ret;            // Valor de retorno del último comando
    int             exit;           // Flag para salir del shell
    int             no_exec;        // Flag para no ejecutar
    char            **env_bin;      // Arreglo de variables de entorno para execve
}               t_ms;

typedef struct s_sig
{
    int            sigint;          // Flag para SIGINT (Ctrl+C)
    int            sigquit;         // Flag para SIGQUIT (Ctrl+\)
    int            exit_status;     // Estado de salida
    pid_t          pid;             // ID del proceso
}               t_sig;

/**
 * Prototypes
 */

// Execution

// Builtins

// Parsing

// Env

// Redirections

// FD tools


// Free tools


// Token tools

// Type tools


// Expansions


// Signal
void	sig_int(int code);
void	sig_quit(int code);
void	sig_init(void);

// Utils

#endif
