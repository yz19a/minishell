/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:27:14 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/08 15:47:02 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Helper functions for command execution
 */

int	decode_error(int err)
{
	int	res;
	int	sig;

	res = 1;
	sig = 0;
	if (WIFEXITED(err))
		res = WEXITSTATUS(err);
	else if (WIFSIGNALED(err))
	{
		sig = WTERMSIG(err);
		if (sig == SIGINT)
			res = 130;
		else if (sig == SIGQUIT)
			res = 131;
		else
			res = 128 + sig;
	}
	return (res);
}

int	is_builtin(char *command)
{
	return (ft_strncmp(command, "cd", 3) == 0
		|| ft_strncmp(command, "env", 4) == 0
		|| ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0
		|| ft_strncmp(command, "exit", 5) == 0
		|| ft_strncmp(command, "echo", 5) == 0);
}

int	execute_builtins(t_command *command, t_shell_data *data, int pipe)
{
	int	status;

	status = 0;
	if (ft_strncmp(command->argv[0], "cd", 3) == 0)
		status = built_in_cd(command, data);
	else if (ft_strncmp(command->argv[0], "env", 4) == 0)
		status = built_in_env(command, data);
	else if (ft_strncmp(command->argv[0], "export", 7) == 0)
		status = built_in_export(command, data);
	else if (ft_strncmp(command->argv[0], "unset", 6) == 0)
		status = built_in_unset(command, data);
	else if (ft_strncmp(command->argv[0], "exit", 5) == 0 && pipe == 1)
		status = 0;
	else if (ft_strncmp(command->argv[0], "exit", 5) == 0 && pipe == 0)
		status = built_in_exit(command, data);
	else if (ft_strncmp(command->argv[0], "echo", 5) == 0)
		status = built_in_echo(command);
	return (status);
}
