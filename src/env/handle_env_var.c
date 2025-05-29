/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:56:04 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/26 14:30:19 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// conseguir el indice de una environment variable dentro de 'char **env',
// siendo var la variable de entorno a encontrar
// devuelve el indice de la variable, o -1 si no la encuentra
int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

// Eliminar una variable de entorno en la posición idx en data->env
// Devuelve 1 (éxito) o 0 (fallo)
int	remove_env_var(t_shell_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_size(data->env))
		return (0);
	free_ptr(data->env[idx]);
	i = idx;
	count = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		count++;
		i++;
	}
	data->env = realloc_env_vars(data, count);
	if (!data->env)
		return (0);
	return (1);
}
