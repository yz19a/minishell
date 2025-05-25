/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 02:23:57 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/06 11:35:45 by jalcausa         ###   ########.fr       */
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

int execute_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
