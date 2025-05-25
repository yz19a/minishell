/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:27 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/25 15:15:55 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Updates PWD and OLDPWD variables
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
 * Function to execute the actual directory change
 */
static int	exec_cd(char *destination_dir, t_shell_data *data)
{
	int		status;
	char	*new_path;

	status = 0;
	if (chdir(destination_dir) == -1)
		status = 1;
	if (destination_dir == 0)
	{
		new_path = getcwd(NULL, 0);
		update_pwds(data, new_path);
		free(new_path);
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

/**
 * 'cd' command implementation
 */
int	built_in_cd(t_command *command, t_shell_data *data)
{
	int		status;
	char	*dest_path;

	status = 1;
	if (command->argc == 1
        || (ft_strncmp(command->argv[1], "--", 3) == 0 && command->argc == 2))
    {
        dest_path = get_env_value(data, "HOME");
        status = exec_cd(dest_path, data);
        free(dest_path);
    }
    // Handle "cd .." (go up one directory)
    else if (command->argc == 2 && ft_strncmp(command->argv[1], "..", 3) == 0)
        status = exec_cd(command->argv[1], data);
    // Handle "cd ." (stay in current directory, just update OLDPWD)
    else if (command->argc == 2 && ft_strncmp(command->argv[1], ".", 2) == 0)
    {
        dest_path = get_env_value(data, "PWD");
        status = set_env_var(data, "OLDPWD", dest_path);
        free(dest_path);
    }
    // Handle "cd path" (go to specified path)
    else if (command->argc >= 2)
        status = exec_cd(command->argv[1], data);
    if (status == 1)
        return (print_error_cd(command->argv[1]));
    return (status);
}
