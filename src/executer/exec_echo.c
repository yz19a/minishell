/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:36 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/26 14:01:18 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Prints the contents of the provided array of strings, which is typically
 * used to display command arguments. Each string is printed in sequence,
 * separated by a space, but no newline is printed at the end.
 *
 * @param aux The array of strings to print.
 */
static void	printmatrix(char **aux)
{
	int	i;

	i = 1;
	while (aux[i])
	{
		ft_printf("%s", aux[i]);
		if (aux[i + 1])
			ft_printf(" ");
		i++;
	}
}

/**
 * Prints all arguments except the first one, which is usually the command name.
 * This function prints each argument followed by a space, but does not print
 * a newline at the end.
 *
 * @param aux The array of strings containing the arguments.
 */
static void	printmatrix_n(char **aux)
{
	int	i;

	i = 2;
	while (aux[i])
	{
		ft_printf("%s", aux[i]);
		if (aux[i + 1])
			ft_printf(" ");
		i++;
	}
}

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
	char	**aux;

	aux = command->argv;
	if (command->argc == 1)
		ft_printf("\n");
	else if (command->argc == 2 && (has_n(command->argv[1]) == 1))
		;
	else if (command->argc >= 2 && (has_n(command->argv[1]) == 0))
	{
		printmatrix(aux);
		ft_printf("\n");
	}
	else
		printmatrix_n(aux);
	return (0);
}
