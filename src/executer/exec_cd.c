/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:27 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/10 17:12:05 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function to update the PWD and OLDPWD environment variables
 * It sets OLDPWD to the current PWD, and PWD to the new directory
 * If new is empty, it sets PWD to OLDPWD
 * @param data Pointer to the shell data structure
 * @param new The new directory to set as PWD
 */
static void	update_pwds(t_shell_data *data, char *new)
{
	char	*oldpwd;
	char	*pwd;

	pwd = get_env_value(data, "PWD");
	set_env_var(data, "OLDPWD", pwd);
	free(pwd);
	if (new[0] == '\0')
	{
		oldpwd = get_env_value(data, "OLDPWD");
		set_env_var(data, "PWD", oldpwd);
		free(oldpwd);
	}
	else
		set_env_var(data, "PWD", new);
}

/**
 * Function to execute the cd command
 * It changes the current working directory to the specified destination_dir
 * If destination_dir is NULL, it updates PWD to the current working directory
 * It returns 0 on success, or 1 if chdir fails
 * @param destination_dir The directory to change to
 * @param data Pointer to the shell data structure containing env vars
 * @return int Returns 0 on success, or 1 on failure
 */
int	exec_cd(char *destination_dir, t_shell_data *data)
{
	int		status;
	char	*newpwd;

	status = 0;
	if (chdir(destination_dir) == -1)
		status = 1;
	else
	{
		newpwd = getcwd(NULL, 0);
		update_pwds(data, newpwd);
		free(newpwd);
	}
	return (status);
}

/**
 * Function to print error message for cd
 * It uses strerror(errno) to show the error chdir() produced
 */
static int	print_error_cd(char *dir)
{
	return (print_error("cd", dir, strerror(errno), 1));
}

static int	auxiliar(char *dir, int argc)
{
	if (argc > 2)
	{
		write(2, "minishell: cd: too many arguments\n", 35);
		return (1);
	}
	else
		return (print_error_cd(dir));
}

/**
 * Function to handle the built-in cd command
 * It checks the number of arguments and calls exec_cd with the appropriate path
 * If no arguments are provided, it changes to the HOME directory
 * If ".." is provided, it changes to the parent directory
 * If "." is provided, it sets OLDPWD to PWD without changing directories
 * If an error occurs, it prints an error message
 * @param command Pointer to the command structure containing the arguments
 * @param data Pointer to the shell data structure containing the env vars
 * @return int Returns 0 on success, or an error code
 */
int	built_in_cd(t_command *command, t_shell_data *data)
{
	int		status;
	char	*dest_path;

	status = 1;
	if (command->argc == 1 || (command->argc == 2
			&& (ft_strncmp(command->argv[1], "--", 3) == 0
				|| ft_strncmp(command->argv[1], "~", 2) == 0)))
	{
		dest_path = get_env_value(data, "HOME");
		status = exec_cd(dest_path, data);
		free(dest_path);
	}
	else if (command->argc == 2 && ft_strncmp(command->argv[1], "-", 2) == 0)
		status = cd_to_oldpwd(data);
	else if (command->argc == 2 && ft_strncmp(command->argv[1], ".", 2) == 0)
	{
		dest_path = get_env_value(data, "PWD");
		status = set_env_var(data, "OLDPWD", dest_path);
		free(dest_path);
	}
	else if (command->argc == 2)
		status = exec_cd(command->argv[1], data);
	if (status == 1 || command->argc > 2)
		return (auxiliar(command->argv[1], command->argc));
	return (status);
}
