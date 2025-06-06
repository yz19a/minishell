/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 10:27:06 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/01 18:19:48 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// reallocate data->env para que tenga un nuevo tamaño, dado como parametro
// size
char	**realloc_env_vars(t_shell_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(new_env));
	if (!new_env)
		return (0);
	i = 0;
	while (data->env[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
		i++;
	}
	free(data->env);
	return (new_env);
}

/**
 * Add the variable to the env
 *
 * If it already exists, it changes it's value
 * Else creates a new one
 *
 */
int	set_env_var(t_shell_data *data, char *key, char *value)
{
	int		idx;
	char	*aux;

	idx = get_env_var_index(data->env, key);
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
		data->env[idx] = ft_strjoin(key, aux);
	}
	free_ptr(aux);
	return (0);
}

char	**realloc_export_env_vars(t_shell_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (0);
	i = 0;
	while (data->exportenv[i] && i < size)
	{
		new_env[i] = ft_strdup(data->exportenv[i]);
		free_ptr(data->exportenv[i]);
		i++;
	}
	free(data->exportenv);
	return (new_env);
}

int	set_export_env_var(t_shell_data *data, char *key, char *value)
{
	int		idx;
	char	*aux;

	idx = get_env_var_index(data->exportenv, key);
	if (!value)
		value = "";
	aux = ft_strjoin("=", value);
	if (!aux)
		return (12);
	if (idx != -1 && data->exportenv[idx])
	{
		free_ptr(data->exportenv[idx]);
		data->exportenv[idx] = ft_strjoin(key, aux);
	}
	else
	{
		idx = env_size(data->exportenv);
		data->exportenv = realloc_export_env_vars(data, idx + 1);
		if (!data->exportenv)
			return (12);
		data->exportenv[idx] = ft_strjoin(key, aux);
	}
	free_ptr(aux);
	return (0);
}

int	remove_exportenv_var(t_shell_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_size(data->exportenv))
		return (0);
	free_ptr(data->exportenv[idx]);
	i = idx;
	count = idx;
	while (data->exportenv[i + 1])
	{
		data->exportenv[i] = ft_strdup(data->exportenv[i + 1]);
		free_ptr(data->exportenv[i + 1]);
		count++;
		i++;
	}
	data->exportenv = realloc_env_vars(data, count);
	if (!data->exportenv)
		return (0);
	return (1);
}
