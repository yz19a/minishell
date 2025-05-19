/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:23:57 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/09 15:53:14 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Contains functions to parse and manipulate environment variables.
 */

// function to free PATH array
void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i])
		i++;
	}
	free(path);
}

// Helper function to compute PATH environment variable
// Split PATH by colon
// Add trailing slash to each directory
static char **compute_path(char *arg)
{
    size_t  i;
    char    *aux;
    char    **res;

    i = 0;
    res = ft_split(arg, ':');
    if (!res)
        return (0);
    while (res[i])
    {
        aux = ft_strjoin(res[i], "/");
        free(res[i]);
        res[i] = aux;
        i++;
    }
    return (res);
}

// Helper function to free array of strings
static char **free_args(char **arg)
{
    if (!arg)
        return (0);
    if (arg[0] != 0)
        free(arg[0]);
    if (arg[1] != 0)
        free(arg[1]);
    free(arg);
    return (0);
}

// Function to get PATH environment variable
// Split environment variable by '='
// Check if variable is PATH
char **get_path(char **env)
{
    char **arg;
    char **res;

    while (env)
    {
        arg = ft_split(*env, '=');
        if (!arg || !arg[0] || !arg[1])
            return (free_args(arg));
        if (ft_strncmp(arg[0], "PATH", 4) == 0)
        {
            res = compute_path(arg[1]);
            free_args(arg);
            return (res);
        }
        else
            free_args(arg);
        env++;
    }
    return (0);
}
