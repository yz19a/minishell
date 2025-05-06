/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:13:50 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/06 11:21:31 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Muestra un prompt personalizado y obtiene el input del usuario usando readline
*/

static char	*get_nextline(void)
{
	char	*prompt;
	char	*line;

	prompt = "minishell > ";
	line = readline(prompt);
	return (line);
}

static t_list	*analyze_line(char **line, t_shell_data *data)
{
	t_list	*tokens;
	//t_list	*commands;

	if (!line || !*line)
	{
		ft_printf("exit\n");
		exit_shell(data, g_sig.exit_status);
	}
	
	expand_variables(line, data, 0);
	tokens = lexer(*line, data);
	/*
	if (!tokens)
		return (0);
	commands = parser(tokens, data);
	lex_free_token_list(&tokens);
	return (commands);
	*/
	return(0);
}

void	shell_loop(t_shell_data *data)
{
	char	*line;

	while (1)
	{
		//Manejo de señales cuando la shell está en modo interactivo
		//(esperando input del usuario)
		set_signals_interactive();
		//Inicializa el campo pid de g_sig a 0 ya que no hay ningún
		//proceso hijo ahora mismo
		sig_init();
		line = get_nextline();
		// Función de la librería Readline para manejo del historial
		add_history(line);
		//Manejo de señales cuando la shell  NO está en modo interactivo
		//(se ha recibido input del usuario)
		set_signals_noninteractive();
		// Extraer comandos del input del usuario
		data->commands = analyze_line(&line, data);
		free(line);
		// Si no hay comandos (se pulsa enter o solo hay espacios
		// volvemos al inicio del bucle)
		if (!data->commands)
			continue ;
		// Si solo hay un comando lo ejecutamos
		/*
		if (ft_lstsize(data->commands) == 1)
			g_sig.exit_status = execute(data->commands, data);
		// Si hay más de un comando necesitamos pipes
		else if (ft_lstsize(data->commands) > 1)
			g_sig.exit_status = execute_pipex(data);
		// Liberar la estructura de comandos
		pars_free_command_list(&(data->commands));
		*/
	}
}
