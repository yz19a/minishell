/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:55 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/26 14:22:38 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to unset environment variables
 * It iterates through the command arguments starting from index 1
 * and removes each variable from both the environment and export environment.
 * If a variable does not exist in either environment, it prints an error
 * message.
 * @param command Pointer to the command structure containing arguments
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns 0 on success, or an error code if a variable does
 * not exist
 */
static int	unset_variables(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;
	int		index_in_env;
	int		index_in_export;

	i = 1;
	args = command->argv;
	while (i < command->argc)
	{
		index_in_env = get_env_var_index(data->env, args[i]);
		index_in_export = get_env_var_index(data->exportenv, args[i]);
		if (index_in_env == -1 || index_in_export == -1)
			return (print_error("unset", args[i], "var does not exist", 1));
		if (index_in_env != -1)
			remove_env_var(data, index_in_env);
		if (index_in_export != -1)
			remove_exportenv_var(data, index_in_export);
		i++;
	}
	return (0);
}

/**
 * Function to handle the built-in unset command
 * It checks the number of arguments and calls unset_variables if there are
 * more than one argument. If there are no arguments, it does nothing.
 * @param command Pointer to the command structure containing arguments
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns 0 if no arguments, or the status from unset_variables
 */
int	built_in_unset(t_command *command, t_shell_data *data)
{
	int	status;

	status = 0;
	if (command->argc == 1)
		;
	else if (command->argc > 1)
		status = unset_variables(command, data);
	return (status);
}
