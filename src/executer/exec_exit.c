/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:43 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/26 14:06:50 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to exit the shell and clean up resources
 * It frees the environment variables, command list, and closes file descriptors
 * Finally, it exits the program with the specified exit code
 * @param data Pointer to the shell data structure containing all shell data
 * @param exitcode The exit code to return to the operating system
 */
void	exitshell(t_shell_data *data, int exitcode)
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

/**
 * Function to check if a string is a valid numeric argument.
 * It iterates through the string and checks if each character is a digit.
 * Returns 1 if the string is numeric, otherwise returns 0.
 * @param str The string to check.
 * @return int Returns 1 if the string is numeric, otherwise 0.
 */
static int	isnum(char *str)
{
	int	i;
	int	is;

	i = 0;
	is = 1;
	if (!str)
		return (0);
	while (str[i] && is)
	{
		is = ft_isdigit(str[i]);
		i++;
	}
	return (is);
}

/**
 * Function to handle the built-in 'exit' command.
 * It checks the number of arguments, validates if the argument is numeric,
 * and exits the shell with the specified exit code.
 * If the argument is not numeric or too many arguments are provided,
 * it prints an error message and returns an error code.
 * @param command Pointer to the command structure containing the arguments.
 * @param data Pointer to the shell data structure containing the env vars.
 * @return int Returns 255 if an error occurs, otherwise it exits the shell.
 */
int	built_in_exit(t_command *command, t_shell_data *data)
{
	int	code;

	ft_printf("exit\n");
	if (command->argc > 2)
	{
		if (!isnum(command->argv[1]))
			exitshell(data,
				print_error("exit", 0, "numeric argument required", 255));
		return (print_error("exit", 0, "too many arguments", 1));
	}
	if (!isnum(command->argv[1]) && command->argc > 1)
		exitshell(data,
			print_error("exit", 0, "numeric argument required", 255));
	else if (command->argc == 1)
		exitshell(data, 0);
	else
	{
		code = ft_atoi(command->argv[1]) % 256;
		exitshell(data, code);
	}
	return (255);
}
