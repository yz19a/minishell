/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:16:12 by yaperalt          #+#    #+#             */
/*   Updated: 2025/05/06 11:35:10 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global_sig	g_sig;

int	main(int argc, char **argv, char **env)
{
	t_shell_data	*shell_data;

	(void)argc;
	(void)argv;
	shell_data = init_shell_data(env);
	shell_loop(shell_data);
	return (0);
}
