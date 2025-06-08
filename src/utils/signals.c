/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 22:34:07 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/08 13:09:26 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Muestra un nuevo prompt en una nueva línea usando funciones de Readline
*/
void	signal_reset_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
Ignora la señal SIGQUIT(ctrl-\) asignándole SIG_IGN al handler
*/
void	ignore_sigquit(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &act, NULL);
}

/*
Manejar señales para el shell en modo interactivo (está esperando input):
SIGINT(ctrl + c) debe resetear el input del usuario a una nueva línea
SIGQUIT(ctrl + \) debe ser ignorada
*/
void	set_signals_interactive(void)
{
	struct sigaction	act;

	ignore_sigquit();
	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &act, NULL);
}

void	print_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

/*
Manejar señales para el shell en modo no interactivo (no se está esperando
input): SIGINT(ctrl + c) y SIGQUIT(ctrl + \) deben ignorarse ya que solo
deben afectar al proceso hijo que está en ejecución. Lo que hacemos es
mostrar una nueva línea únicamente
*/
void	set_signals_noninteractive(void)
{
    struct sigaction	act;

    ft_memset(&act, 0, sizeof(act));
    act.sa_handler = SIG_IGN;
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGQUIT, &act, NULL);
}
