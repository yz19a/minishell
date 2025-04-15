/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:13:50 by jalcausa          #+#    #+#             */
/*   Updated: 2025/04/15 22:51:14 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Muestra un prompt personalizado y obtiene el input del usuario usando readline
*/

static char	*get_nextline(void)
{
	char	*name;
	char	*prompt;
	char	*line;

	name = "minishell ";
	prompt = ft_strjoin(name, " > ");
	line = readline(prompt);
	return (free(prompt), line);
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
		add_history(line);
		//Manejo de señales cuando la shell  NO está en modo interactivo
		//(se ha recibido input del usuario)
		set_signals_noninteractive();
		// Extraer comandos del input del usuario
		data->commands = analyze_line(&line, data);
		free(line);
		// Si no hya comandos (se pulsa enter o solo hay espacios
		// volvemos al inicio del bucle)
		if (!data->commands)
			continue ;
		// Si solo hay un comando lo ejecutamos
		if (ft_lstsize(data->commands) == 1)
			g_sig.exit_status = execute(data->commands, data);
		// Si hay más de un comando necesitamos pipes
		else if (ft_lstsize(data->commands) > 1)
			g_sig.exit_status = execute_pipex(data);
		// Liberar la estructura de comandos
		pars_free_command_list(&(data->commands));
	}
}
