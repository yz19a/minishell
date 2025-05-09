/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:27:14 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/09 15:52:58 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Helper functions for command execution
 */

// interpret status code returned by a child processs after wait()
// if the child didn't terminate normally it returns 1 as default error code
int	decode_error(int err)
{
	int	res;

	res = 1;
	if(WIFEXITED(err))
		res = WEXITSTATUS(err);
	return (res);
}

// function to check if command is a built-in
int	is_builtin(char *command)
{
	return (ft_strncmp(command, "cd", 3) == 0
		|| ft_strncmp(command, "env", 4) == 0
		|| ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0
		|| ft_strncmp(command, "exit", 5) == 0
		|| ft_strncmp(command, "echo", 5) == 0);
}

// function to execute built-in commands
int	execute_builtins(t_command *command, t_shell_data *data)
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
	else if (ft_strncmp(command->argv[0], "exit", 5) == 0)
		status = built_in_exit(command, data);
	else if (ft_strncmp(command->argv[0], "echo", 5) == 0)
		status = built_in_echo(command);
	return (status);
}
