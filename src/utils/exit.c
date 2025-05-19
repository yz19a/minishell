/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:42:28 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/06 11:34:21 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_shell(t_shell_data *data, int exitcode)
{
	if (data)
	{
		free_envs(data);
		ft_lstclear(&data->commands, del_t_command);
		if (data->dup_stdin)
			close(data->dup_stdin);
		if (data->dup_stdout)
			close(data->dup_stdout);
		free(data);
	}
	exit(exitcode);
}
