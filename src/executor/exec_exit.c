/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:43 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/09 15:53:33 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Implements the exit command to terminate the shell.
 */

// Function to clean up and exit the shell
void exitshell(t_shell_data *data, int exitcode)
{
    if (data)
    {
        // Clean up all shell data
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

// Helper function to check if a string is a number
static int isnum(char *str)
{
    int i;
    int is;

    i = 0;
    is = 1;
    if (!str)
        return (0);

    // Check each character is a digit
    while (str[i] && is)
    {
        is = ft_isdigit(str[i]);
        i++;
    }
    return (is);
}

int built_in_exit(t_command *command, t_shell_data *data)
{
    int code;

    ft_printf("exit\n");

    // Handle too many arguments
    if (command->argc > 2)
    {
        if (!isnum(command->argv[1]))
            exitshell(data,
                print_error("exit", 0, "numeric argument required", 255));
        return (print_error("exit", 0, "too many arguments", 1));
    }
    // Handle non-numeric exit code
    if (!isnum(command->argv[1]) && command->argc > 1)
        exitshell(data,
            print_error("exit", 0, "numeric argument required", 255));
    // Handle no arguments (exit with 0)
    else if (command->argc == 1)
        exitshell(data, 0);
    // Handle numeric exit code
    else
    {
        code = ft_atoi(command->argv[1]) % 256;
        exitshell(data, code);
    }
    return (255);
}
