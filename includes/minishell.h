/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:07:21 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/26 13:37:51 by yaperalt         ###   ########.fr       */
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
# include <sys/wait.h>

/* Structures */

typedef struct s_command
{
	char	**argv;
	int		argc;
	int		fd_in;
	int		fd_out;
}	t_command;

typedef struct s_shell_data
{
	char	**env;
	int		dup_stdin;
	int		dup_stdout;
	t_list	*commands;
	char	**exportenv;
}	t_shell_data;

/* Function Prototypes */

/* main.c */
int				main(int argc, char **argv, char **env);

/* shell_loop.c */
void			shell_loop(t_shell_data *data);

/* utils/init.c */
t_shell_data	*init_shell_data(char **env);
int				env_size(char **env);
int				init_env(t_shell_data *aux, char **env);
int				init_export_env(t_shell_data *aux, char **env);

/* utils/signals.c */
void			set_signals_interactive(void);
void			ignore_sigquit(void);
void			signal_reset_prompt(int signal);
void			print_newline(int signal);
void			set_signals_noninteractive(void);

/* utils/free.c */
void			free_ptr(void *ptr);
void			free_envs(t_shell_data *data);
void			del_t_command(void *com);
void			free_command(t_command *cmd);
void			free_exportenv(char **exportenv);

/* utils/exit.c */
void			exit_shell(t_shell_data *data, int exitcode);

/* utils/expand_variables.c */
void			expand_variables(char **line, t_shell_data *data,
					int expand_quotes);
char			*expand_env_var(char *var, t_shell_data *data);

/* utils/errors.c */
char			*join_strs(char *str, char *add);
int				print_error(char *command, char *detail, char *error_message,
					int err);

/* utils/pipes.c */
void			close_pipes(t_shell_data *data, t_list *instr);

/* env/get_env_value.c */
char			*get_env_value(t_shell_data *data, char *key);

/* env/split_env.c */
char			**split_env(char *str);

/* env/set_env_var.c */
int				set_env_var(t_shell_data *data, char *name, char *value);
int				set_export_env_var(t_shell_data *data, char *key, char *value);
int				remove_exportenv_var(t_shell_data *data, int idx);
char			**realloc_export_env_vars(t_shell_data *data, int size);

/* env/handle_env_var.c */
int				get_env_var_index(char **env, char *var);
int				remove_env_var(t_shell_data *data, int idx);
char			**realloc_env_vars(t_shell_data *data, int size);

/* env/parse_env.c */
char			**get_path(char **env);
void			free_path(char **path);

/* executer/executer.c */
char			*check_access(char *command, char **path);
int				execute(t_list *instr, t_shell_data *data);
int				execute_pipex(t_shell_data *data);

/* executer/executer_utils.c */
int				decode_error(int err);
int				is_builtin(char *command);
int				execute_builtins(t_command *command, t_shell_data *data);

/* executer/exec_cd.c */
int				built_in_cd(t_command *command, t_shell_data *data);

/* executer/exec_echo.c */
int				built_in_echo(t_command *command);

/* executer/exec_env.c */
int				built_in_env(t_command *command, t_shell_data *data);

/* executer/exec_exit.c */
void			exitshell(t_shell_data *data, int exitcode);
int				built_in_exit(t_command *command, t_shell_data *data);

/* executer/exec_export.c */
int				built_in_export(t_command *command, t_shell_data *data);

/* executer/exec_pwd.c */
int				exec_pwd(void);

/* executer/exec_unset.c */
int				built_in_unset(t_command *command, t_shell_data *data);

/* parser/lexer/lexer.c */
t_list			*lexer(char *command, t_shell_data *data);
t_lex_st		lex_next_state(t_lex_st state, char cur_char);

/* parser/lexer/states.c */
void			lex_quote_states(char **line, t_lex_st *st, t_list **res,
					char quote);
void			lex_word_state(char **line, t_lex_st *st, t_list **res);
void			lex_start_state(char **line, t_lex_st *state, t_list **res);

/* parser/lexer/utils.c */
t_list			*lex_create_token(t_token_type type, char *content);
void			append_last_token(t_list **tokens, char **cmd);
void			lex_free_token_list(t_list **lst);

/* parser/parser/parser.c */
t_list			*parser(t_list *tokens, t_shell_data *data);
t_pars_st		pars_next_state(t_pars_st st, t_token *tok);

/* parser/parser/states.c */
t_pars_err		pars_start_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_command_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_redirin_st(t_list *tokens, t_pars_st *state,
					t_list **commands);
t_pars_err		pars_redirout_st(t_list *tokens, t_pars_st *state,
					t_list **cmds);
t_pars_err		pars_rediroappe_st(t_list *tokens, t_pars_st *state,
					t_list **cmds);

/* parser/parser/states2.c */
t_pars_err		pars_redheredoc_st(t_list *tokens, t_pars_st *state,
					t_list **cmds, t_shell_data *data);
t_pars_err		pars_invalid_st(t_list *tokens, t_pars_st *state);

/* parser/parser/actions.c */
t_pars_err		pars_set_stdin(t_list *commands, char *filename);
t_pars_err		pars_set_stdout(t_list *commands, char *filename, int append);
t_pars_err		pars_append_arg_to_command(t_list *commands, char *value);
t_pars_err		pars_append_new_command(t_list **commands, char *value);

/* parser/parser/actions_heredoc.c */
t_pars_err		pars_create_heredoc(t_list *cmds, char *value,
					t_shell_data *data);

/* parser/parser/utils.c */
void			pars_free_command_list(t_list **cmds);

/* utils.c */
void			print_prompt(void);
void			clear_input_buffer(void);

/* Global signal */
extern int	g_exit_status;

#endif
