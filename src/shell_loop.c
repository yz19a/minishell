/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:13:50 by jalcausa          #+#    #+#             */
/*   Updated: 2025/04/07 23:15:46 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_nextline(void)
{
	char	*aux;
	char	*current_dir;
	char	*prompt;
	char	*line;

	current_dir = getcwd(NULL, 0);
	aux = ft_strjoin("ConchaBB ", current_dir);
	prompt = ft_strjoin(aux, " > ");
	line = readline(prompt);
	return (free(current_dir), free(aux), free(prompt), line);
}

static t_list	*analyze_line(char **line, t_shell_data *data)
{
	t_list	*tokens;
	t_list	*commands;

	if (!line || !*line)
	{
		ft_printf("exit\n");
		exitshell(data, g_sig.exit_status);
	}
	expand_variables(line, data, 0);
	tokens = lexer(*line, data);
	if (!tokens)
		return (0);
	commands = parser(tokens, data);
	lex_free_token_list(&tokens);
	return (commands);
}

void	shell_loop(t_shell_data *data)
{
	char	*line;

	data->dup_stdin = dup(STDIN_FILENO);
	data->dup_stdout = dup(STDOUT_FILENO);
	while (1)
	{
		set_signals_interactive();
		sig_init();
		line = get_nextline();
		add_history(line);
		set_signals_noninteractive();
		data->commands = analyze_line(&line, data);
		free(line);
		if (!data->commands)
			continue ;
		if (ft_lstsize(data->commands) == 1)
			g_sig.exit_status = execute(data->commands, data);
		else if (ft_lstsize(data->commands) > 1)
			g_sig.exit_status = execute_pipex(data);
		pars_free_command_list(&(data->commands));
	}
}
