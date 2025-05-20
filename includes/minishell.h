/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:07:21 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/19 20:23:18 by jalcausa         ###   ########.fr       */
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

// expand_variables.c
void	expand_variables(char **line, t_shell_data *data, int expand_quotes);

// env
char	*get_env_value(t_shell_data *data, char *key);
char	**split_env(char *str);

// errors.c
char	*join_strs(char *str, char *add);
int	print_error(char *command, char *detail, char *error_message, int err);

// LEXER
// lexer.c
t_list	*lexer(char *command, t_shell_data *data);
t_lex_st	lex_next_state(t_lex_st state, char cur_char);

// states.c
void	lex_quote_states(char **line, t_lex_st *st, t_list **res, char quote);
void	lex_word_state(char **line, t_lex_st *st, t_list **res);
void	lex_start_state(char **line, t_lex_st *state, t_list **res);

// utils.c
t_list	*lex_create_token(t_token_type type, char *content);
void	append_last_token(t_list **tokens, char **cmd);
void	lex_free_token_list(t_list **lst);

// PARSER
// parser.c
t_list	*parser(t_list *tokens, t_shell_data *data);
t_pars_st	pars_next_state(t_pars_st st, t_token *tok);

//states.c
t_pars_err	pars_start_st(t_list *tokens, t_pars_st *state,
	t_list **commands);
t_pars_err	pars_command_st(t_list *tokens, t_pars_st *state,
	t_list **commands);
t_pars_err	pars_redirin_st(t_list *tokens, t_pars_st *state,
	t_list **commands);
t_pars_err	pars_redirout_st(t_list *tokens, t_pars_st *state,
	t_list **cmds);
t_pars_err	pars_rediroappe_st(t_list *tokens, t_pars_st *state,
	t_list **cmds);

// states2.c
t_pars_err	pars_redheredoc_st(t_list *tokens, t_pars_st *state,t_list **cmds,
	t_shell_data *data);
t_pars_err	pars_invalid_st(t_list *tokens, t_pars_st *state);

// actions.c
t_pars_err	pars_set_stdin(t_list *commands, char *filename);
t_pars_err	pars_set_stdout(t_list *commands, char *filename, int append);
t_pars_err	pars_append_arg_to_command(t_list *commands, char *value);
t_pars_err	pars_append_new_command(t_list **commands, char *value);

// actions_heredoc.h
t_pars_err	pars_create_heredoc(t_list	*cmds, char *value, t_shell_data *data);

// utils.c
void	pars_free_command_list(t_list **cmds);


extern t_global_sig	g_sig;

#endif