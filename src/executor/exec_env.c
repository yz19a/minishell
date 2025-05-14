/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:39 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/09 15:27:44 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Implements the env command to display environment variables.
 */
int built_in_env(t_command *command, t_shell_data *data)
{
    int     res_code;
    char    **envaux;
    int     i;

    res_code = 0;
    i = 0;
    envaux = data->env;

    // If no arguments, print all environment variables
    if (command->argc == 1)
    {
        while (i < env_size(envaux))
        {
            printf("%s\n", envaux[i]);
            i++;
        }
    }
    // If arguments provided, print error (env doesn't take arguments)
    else
        return (print_error("env", 0,
                "Error, env built in doesnt support any arguments or flags",
                1));
    return (res_code);
}
