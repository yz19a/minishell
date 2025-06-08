/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:36 by yaperalt          #+#    #+#             */
/*   Updated: 2025/06/08 15:10:23 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Checks if the first argument is "-n" and returns 1 if true, 0 otherwise.
 * This function checks if the string starts with "-n" and ensures that
 * all characters after "-" are 'n'.
 *
 * @param text The string to check.
 * @return 1 if it starts with "-n", 0 otherwise.
 */
static int	has_n(char *text)
{
	int	i;
	int	hasn;

	hasn = 0;
	i = 0;
	if (ft_strncmp(text, "-n", 2) != 0)
		return (hasn);
	else
	{
		i++;
		while (text[i] && text[i] == 'n')
			i++;
		if (text[i] == '\0')
			hasn = 1;
	}
	return (hasn);
}

/**
 *		Main echo implementation
 *
 *      If no arguments, print newline
 *		If only -n flag, print nothing (no newline)
 *		If arguments without -n flag, print all with newline
 *		If arguments with -n flag, print all without newline
 *		Returns 0 on success.
 *
 */
int	built_in_echo(t_command *command)
{
	int		i;
	int		n_flag;

	i = 1;
	n_flag = 0;
	while (i < command->argc && has_n(command->argv[i]))
	{
		n_flag = 1;
		i++;
	}
	while (i < command->argc)
	{
		ft_printf("%s", command->argv[i]);
		if (i + 1 < command->argc)
			ft_printf(" ");
		i++;
	}
	if (!n_flag)
		ft_printf("\n");
	return (0);
}
