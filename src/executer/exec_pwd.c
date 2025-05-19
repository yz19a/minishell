/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:36:51 by yaperalt          #+#    #+#             */
/*   Updated: 2025/04/22 22:19:11 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
