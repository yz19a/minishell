/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:16:12 by yaperalt          #+#    #+#             */
/*   Updated: 2025/03/23 15:44:35 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_prototypes.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	if (argc != 1 || !argv[1])
	{
		ft_printf("\nThis program doesn't accept arguments.\n\n");
		return (1);
	}
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	g_signals.heredoc = false;
	g_signals.builtin = true;
	return (0);
}
