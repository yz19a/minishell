/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:16:12 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/25 16:57:48 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_status;

int	main(int argc, char **argv, char **env)
{
	t_shell_data	*shell_data;

	(void)argc;
	(void)argv;
	shell_data = init_shell_data(env);
	shell_loop(shell_data);
	return (0);
}
