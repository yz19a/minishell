/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:47:54 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/06 12:17:18 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	free_envs(t_shell_data *data)
{
	int	i;

	i = 0;
	if (data->env)
	{
		while (data->env[i])
		{
			free_ptr(data->env[i]);
			i++;
		}
		free_ptr(data->env);
		data->env = NULL;
	}
	i = 0;
	if (data->exportenv)
	{
		while (data->exportenv[i])
		{
			free_ptr(data->exportenv[i]);
			i++;
		}
		free_ptr(data->exportenv);
		data->exportenv = NULL;
	}
}

void	del_t_command(void *com)
{
	t_command	*command;
	int			i;

	command = (t_command *) com;
	if (command->fd_in)
		close(command->fd_in);
	if (command->fd_out)
		close(command->fd_out);
	i = 0;
	while (command->argv[i])
	{
		free_ptr(command->argv[i]);
		i++;
	}
	free_ptr(command->argv);
}
