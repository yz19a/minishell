/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:23:57 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/30 15:08:16 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Implements the pwd command to print working directory.
 * @param 1 getcwd() = Pointer where the path will be stored.
 * @param 2 getcwd() = The maximum number of bytes to write into buf.
 * By passing NULL as the buffer, getcwd() allocates memory automatically
 * using malloc().
 */

int	exec_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
