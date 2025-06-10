/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:20:41 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/09 18:17:29 by jalcausa         ###   ########.fr       */
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

/*
Verifica si una cadena contiene solo espacios en blanco
*/
int	is_only_whitespace(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}
