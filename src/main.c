/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:16:12 by yaperalt          #+#    #+#             */
/*   Updated: 2025/03/29 17:01:13 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_sig	g_sig;

void	init_ms2(t_ms *ms, t_token *token)
{
	ms->charge = 1;
	ms->parent = 1;
	ms->last = 1;
	signal(SIGQUIT, &sig_quit);
	redir_and_exec(ms, token);
	reset_std(ms);
	close_fds(ms);
	reset_fds(ms);
}

void	minishell(t_ms *ms)
{
    t_token *token;
    int 	status;
    
    // Encuentra el primer token para ejecutar
    token = next_run(ms->start, NOSKIP);
    if (is_types(ms->start, "TAIH"))
        token = ms->start->next;
        
    // Bucle de ejecución de comandos
    while (ms->exit == 0 && token) {
        init_ms2(ms, token);        // Inicializa para este comando
        waitpid(-1, &status, 0);    // Espera a que termine el proceso hijo
        status = WEXITSTATUS(status);
        
        // Actualiza el valor de retorno
        if (ms->last == 0)
            ms->ret = status;
            
        // Si es proceso hijo, termina
        if (ms->parent == 0) {
            free_token(ms->start);
            exit(ms->ret);
        }
        
        ms->no_exec = 0;
        token = next_run(token, SKIP); // Obtiene el siguiente comando
    }
}

void	init_ms(t_ms *ms, char **env)
{
	ms->fds.dup_in = dup(STDIN);
	ms->fds.dup_out = dup(STDOUT);
	ms->exit = 0;
	ms->ret = 0;
	ms->no_exec = 0;
	ms->env_bin = env;
}

int main(int argc, char **argv, char **env)
{
    t_ms ms;

	(void)argc;
	(void)argv;
	init_ms(&ms, env);		   // Inicializa la estructura principal
	reset_fds(&ms);            // Reinicia los descriptores de archivo
    env_init(&ms, env);        // Inicializa las variables de entorno
    secret_env_init(&ms, env); // Inicializa las variables de entorno ocultas
    
    // Bucle principal
    while (ms.exit == 0) {
        sig_init();            // Inicializa el manejo de señales
        ms.start = NULL;       // Reinicia la lista de tokens
        reset_std(&ms);        // Restaura stdin/stdout estándar
        parse(&ms);            // Analiza la entrada del usuario
        if (ms.start != NULL && check_line(&ms, ms.start))
            minishell(&ms);    // Ejecuta el shell
        if (ms.start)
            free_token(ms.start); // Libera la memoria de los tokens
    }
    
    // Limpieza final
    free_env(ms.env);
    free_env(ms.secret_env);
    return (ms.ret);
}
