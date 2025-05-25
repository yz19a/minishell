/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:36 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/09 15:53:43 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Implements the echo command to print text.
 */

// Helper function to print all arguments
static void printmatrix(char **aux)
{
    int i;

    i = 1;
    while (aux[i])
    {
        ft_printf("%s", aux[i]);
        if (aux[i + 1])
            ft_printf(" ");
        i++;
    }
}

// Helper function to print all arguments when -n flag is used
static void printmatrix_n(char **aux)
{
    int i;

    // Start from index 2 to skip "echo" and "-n"
    i = 2;
    while (aux[i])
    {
        ft_printf("%s", aux[i]);
        if (aux[i + 1])
            ft_printf(" ");
        i++;
    }
}

// Helper function to check if an argument is the -n flag
static int has_n(char *text)
{
    int i;
    int hasn;

    hasn = 0;
    i = 0;
    // Check if it starts with "-n"
    if (ft_strncmp(text, "-n", 2) != 0)
        return (hasn);
    else
    {
        i++;
        // Ensure all characters after "-" are 'n'
        while (text[i] && text[i] == 'n')
            i++;
        if (text[i] == '\0')
            hasn = 1;
    }
    return (hasn);
}

// Main echo implementation
int built_in_echo(t_command *command)
{
    char **aux;

    aux = command->argv;
    // If no arguments, just print newline
    if (command->argc == 1)
        ft_printf("\n");
    // If only -n flag, print nothing (no newline)
    else if (command->argc == 2 && (has_n(command->argv[1]) == 1))
        ;
    // If arguments without -n flag, print all with newline
    else if (command->argc >= 2 && (has_n(command->argv[1]) == 0))
    {
        printmatrix(aux);
        ft_printf("\n");
    }
    // If arguments with -n flag, print all without newline
    else
        printmatrix_n(aux);
    return (0);
}
