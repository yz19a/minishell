/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:39 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/26 13:54:05 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Executes the built-in 'env' command.
 * @param command Pointer to the command structure containing the arguments.
 * @param data Pointer to the shell data structure containing the env vars.
 * @return int Returns 0 on success, or an error code.
 */
int	built_in_env(t_command *command, t_shell_data *data)
{
	int		res_code;
	char	**envaux;
	int		i;

	res_code = 0;
	i = 0;
	envaux = data->env;
	if (command->argc == 1)
	{
		while (i < env_size(envaux))
		{
			printf("%s\n", envaux[i]);
			i++;
		}
	}
	else
		return (print_error("env", 0,
				"Error, env built in doesnt support any arguments or flags",
				1));
	return (res_code);
}
