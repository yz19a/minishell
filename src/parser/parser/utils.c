/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:20:41 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/19 20:20:53 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_node(void *node)
{
	t_command	*command;
	int			i;

	if (!node)
		return ;
	command = (t_command *) node;
	i = 0;
	while (command->argv[i])
	{
		free(command->argv[i]);
		i++;
	}
	free(command->argv);
	free(command);
}

void	pars_free_command_list(t_list **cmds)
{
	if (!cmds)
		return ;
	ft_lstclear(cmds, &free_node);
}