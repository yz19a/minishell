/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:20:04 by jalcausa          #+#    #+#             */
/*   Updated: 2025/04/09 23:54:16 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int init_env(t_shell_data *aux, char **env)
{
    int i;

    i = 0;
    aux->env = ft_calloc(env_size(env) + 1, sizeof(char *));
    if (!aux->env)
        return (0);
    
    while (env[i])
    {
        aux->env[i] = ft_strdup(env[i]);
        if (!aux->env[i])
        {
            int j = 0;
            while (j < i)
            {
                free(aux->env[j]);
                j++;
            }
            free(aux->env);
            aux->env = NULL;
            return (0);
        }
        i++;
    }
    return (1);
}

int init_export_env(t_shell_data *aux, char **env)
{
    int i;

    i = 0;
    aux->exportenv = ft_calloc(env_size(env) + 1, sizeof(char *));
    if (!aux->exportenv)
        return (0);
    
    while (env[i])
    {
        aux->exportenv[i] = ft_strdup(env[i]);
        if (!aux->exportenv[i])
        {
            int j = 0;
            while (j < i)
            {
                free(aux->exportenv[j]);
                j++;
            }
            free(aux->exportenv);
            aux->exportenv = NULL;
            return (0);
        }
        i++;
    }
    return (1);
}

/* 
Inicializar los datos de la shell:
- Inicializamos el campo exit_status de la variable global que almacena
el código de salida del último comando ejecutado a 0 porque todavía no
hemos ejecutado ninguno (0 para indicar que no hay fallos)
-Al hacer ft_calloc nos aseguramos que todos los punteros son null
y todos los enteros son 0 en la estructura
-Inicializamos env (variables de entorno iniciales) con las que se nos pasan
como argumento en el main.
-Guardamos un duplicado de la salida y entrada estándar para poder resturarlos
en caso de que los cambiemos por una redirección
-Inicializamos también las exportenv que mantendrán las variables de entorno
originales y las que vayamos creando con EXPORT
*/
t_shell_data	*init_shell_data(char **env)
{
	t_shell_data	*aux;
	
	g_sig.exit_status = 0;
	aux = (t_shell_data *)ft_calloc(1, sizeof(t_shell_data));
	init_env(aux, env);
	aux->dup_stdin = dup(STDIN_FILENO);
	aux->dup_stdout = dup(STDOUT_FILENO);
	init_export_env(aux, env);
	return (aux);
}