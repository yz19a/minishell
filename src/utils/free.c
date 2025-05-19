/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:47:54 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/06 11:34:34 by jalcausa         ###   ########.fr       */
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
	while (data->env[i])
	{
		free_ptr(data->env[i]);
		i++;
	}
	free_ptr(data->env);
	i = 0;
	while (data->exportenv[i])
	{
		free_ptr(data->exportenv[i]);
		i++;
	}
	free_ptr(data->exportenv);
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