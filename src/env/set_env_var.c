/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 10:27:06 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/25 10:39:35 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Add the variable to the env
 *
 * If it already exists, it changes it's value
 * Else creates a new one
 *
 */
int	set_env_var(t_shell_data *data, char *name, char *value)
{
	int		idx;
	char	*aux;

	idx = get_env_var_index(data->env, name);
	if (value == NULL)
		value = "";
	aux = ft_strjoin("=", value);
	if (!aux)
		return (12);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, aux);
	}
	else
	{
		idx = env_size(data->env);
		data->env = realloc_env_vars(data, idx + 1);
		if (!data->env)
			return (12);
		data->env[idx] = ft_strjoin(name, value);
	}
	free(aux);
	return (0);
}
