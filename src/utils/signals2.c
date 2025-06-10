/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:30:38 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/10 18:57:19 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Handler para SIGINT en modo no interactivo - muestra ^C y nueva línea
*/
void	signal_noninteractive_sigint(int signal)
{
	(void)signal;
	write(1, "^C\n", 3);
}

/*
Handler para SIGQUIT en modo no interactivo - muestra ^\ y nueva línea
*/
void	signal_noninteractive_sigquit(int signal)
{
	(void)signal;
	write(1, "^\\\n", 3);
}

/*
Guarda la configuración actual del terminal y deshabilita el eco de control
*/
void	disable_control_echo(void)
{
	struct termios	current_termios;
	struct termios	new_termios;

	if (tcgetattr(STDIN_FILENO, &current_termios) == 0)
	{
		new_termios = current_termios;
		new_termios.c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	}
}

/*
Restaura el eco de caracteres de control
*/
void	enable_control_echo(void)
{
	struct termios	current_termios;
	struct termios	new_termios;

	if (tcgetattr(STDIN_FILENO, &current_termios) == 0)
	{
		new_termios = current_termios;
		new_termios.c_lflag |= ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
	}
}
