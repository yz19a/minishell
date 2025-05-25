/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:55 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/25 15:16:19 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implements the unset command to remove an environment variable.
 */

// helper function to unset multiple variables
static int unset_variables(t_command *command, t_shell_data *data)
{
	int     i;
    char    **args;
    int     index_in_env;
    int     index_in_export;

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

// unset implementation
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
