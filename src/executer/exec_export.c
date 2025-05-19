/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:47 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/15 07:45:16 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Implements the export command to set/display environment variables.
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

}


// helper function check if variable name is valid
static int	is_valid_name(char *arg)
{

}

/**
 * If variable without =, it's stored only in EXPORT
 * If variable with = but no value, stored in ENV and EXPORT with empty value
 * Other wise stored in ENV and EXPORT with the values
 */

static int	set_infinite_vars(t_command *command, t_shell_data *data)
{

}

// main export implementation
