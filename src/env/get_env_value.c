/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 00:15:33 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/26 14:29:50 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*free_args(char **arg)
{
	if (!arg)
		return (0);
	if (arg[0] != 0)
		free(arg[0]);
	if (arg[1] != 0)
		free(arg[1]);
	free(arg);
	return (0);
}

char	*get_env_value(t_shell_data *data, char *key)
{
	char	**arg;
	char	*res;
	size_t	key_len;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	while (data->env[i])
	{
		arg = split_env(data->env[i]);
		if (!arg || !arg[0] || !arg[1])
			return (free_args(arg));
		if (ft_strncmp(arg[0], key, key_len) == 0)
		{
			res = ft_strdup(arg[1]);
			free_args(arg);
			return (res);
		}
		else
			free_args(arg);
		i++;
	}
	return (0);
}
