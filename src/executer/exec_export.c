/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:47 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/25 15:47:28 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implements the export command to set/display environment variables.
 * export VARIABLE_NAME=value creates a new environment variable
 * running export without args displays a list of all environment variables,
 * that have been exported in the current shell session
 */

// helper function to free array of strings
static void	free_args(char **arg)
{
	int	i;

	i = 0;
	if (!arg)
		return;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg[i]);
}

// helper function to print evironment variables in export format
static void	print_export_env(t_shell_data *data)
{
	char	**export_env_aux;
	int		i;
	char	**iterator;

	i = 0;
	export_env_aux = data->exportenv;
	while (i < env_size(export_env_aux))
    {
        iterator = ft_split(export_env_aux[i], '=');
        if (!iterator[1])
            printf("declare -x %s\n", iterator[0]);
        else
            printf("declare -x %s=\"%s\"\n", iterator[0], iterator[1]);
        free_args(iterator);
        i++;
    }
}


// helper function check if variable name is valid
static int	is_valid_name(char *arg)
{
	char	*invalid_chars;
	int		i;
	int		is_valid;
	char	**splitted;

	i = 0;
	is_valid = 1;
	invalid_chars = ":-!/?+^.,";
	if (arg[0] == '=')
		return (0);
	splitted = ft_split(arg, '=');
	 while (((i < (int)ft_strlen(splitted[0]))) && (is_valid == 1))
    {
        if (ft_strchr(invalid_chars, splitted[0][i])
            || ft_isdigit(splitted[0][0]))
            is_valid = 0;
        i++;
    }
    free_args(splitted);
    return (is_valid);
}

/**
 * If variable without =, it's stored only in EXPORT
 * If variable with = but no value, stored in ENV and EXPORT with empty value
 * Other wise stored in ENV and EXPORT with the values
 *
 */
static int	set_variables(t_command *command, t_shell_data *data)
{
	int		i;
	char	**args;
	char	**splitted;

	i = 0;
	args = command->argv;
	while (++i < command->argc)
	{
		if (is_valid_name(args[i]))
        {
            if (!ft_strchr(args[i], '='))
                set_export_env_var(data, args[i], "");
            else
            {
                splitted = ft_split(args[i], '=');
                set_env_var(data, splitted[0], splitted[1]);
                set_export_env_var(data, splitted[0], splitted[1]);
                free_args(splitted);
            }
        }
        else
            return (print_error("export", args[i], "not a valid identifier",
                    1));
	}
	return (0);
}

// main export implementation
int	built_in_export(t_command *command, t_shell_data *data)
{
	int	status;

	status = 0;
	if (command->argc == 1)
		print_export_env(data);
	else if (command->argc > 1)
		status = set_variables(command, data);
	return (status);
}
