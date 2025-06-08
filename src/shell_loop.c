/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:13:50 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/08 15:41:31 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * get_nextline - Prompts the user for input and returns the next line.
 */
static char	*get_nextline(void)
{
	char	*prompt;
	char	*line;

	prompt = "minishell > ";
	line = readline(prompt);
	return (line);
}

/**
 * analyze_line - Analyzes the input line, expands variables, tokenizes,
 *                and parses it into commands.
 * @line: Pointer to the input line to be analyzed.
 * @data: Pointer to the shell data structure containing env vars and state.
 *
 * This function handles variable expansion, tokenization, and parsing of the
 * input line into a list of commands. It returns a list of parsed commands
 * or NULL if an error occurs.
 */
static t_list	*analyze_line(char **line, t_shell_data *data)
{
	t_list	*tokens;
	t_list	*commands;

	if (!line || !*line)
	{
		ft_printf("exit\n");
		exit_shell(data, g_exit_status);
	}
	expand_variables(line, data, 0);
	tokens = lexer(*line, data);
	if (!tokens)
		return (0);
	commands = parser(tokens, data);
	lex_free_token_list(&tokens);
	return (commands);
	return (0);
}

/**
 * shell_loop - Main loop of the shell.
 * @data: Pointer to the shell data structure containing env vars and state.
 *
 * This function continuously prompts the user for input, processes the input,
 * and executes commands until the shell is exited.
 * It handles both single commands and piped commands, managing the command list
 * and executing them accordingly.
 * It also sets up signal handling for interactive mode.
 */
void	shell_loop(t_shell_data *data)
{
	char	*line;

	while (1)
	{
		set_signals_interactive();
		line = get_nextline();
		add_history(line);
		set_signals_noninteractive();
		data->commands = analyze_line(&line, data);
		free(line);
		if (!data->commands)
			continue ;
		set_signals_noninteractive();
		if (ft_lstsize(data->commands) == 1)
			g_exit_status = execute(data->commands, data, 0);
		else
			g_exit_status = execute_pipex(data);
		set_signals_interactive();
		pars_free_command_list(&(data->commands));
	}
}
