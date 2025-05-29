/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:12:50 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/25 19:45:39 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Une dos strings, liberando el primero, si hay un error devuelve NULL
char	*join_strs(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free_ptr(tmp);
	return (str);
}

// Detecta si el comando que produce el error es export o unset
// para añadir comillas o no
static int	add_detail_quotes(char *command)
{
	return (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0);
}

// Imprime el error por la salida estándar precedido del nombre
// del programa y donde se produce. Devuelve el codigo del error
int	print_error(char *cmd, char *detail, char *err_msg, int err)
{
	char	*msg;
	int		detail_quotes;

	detail_quotes = add_detail_quotes(cmd);
	msg = ft_strdup("minishell: ");
	if (cmd != NULL)
	{
		msg = join_strs(msg, cmd);
		msg = join_strs(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, detail);
		if (detail_quotes)
			msg = join_strs(msg, "'");
		msg = join_strs(msg, ": ");
	}
	msg = join_strs(msg, err_msg);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (err);
}
