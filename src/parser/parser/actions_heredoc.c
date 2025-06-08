/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:18:13 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/08 15:25:58 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	read_heredoc(int fd, char *value, t_shell_data *data)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline(" >> ");
		if (!line)
		{
			printf("\n");
			break;
		}
		expand_variables(&line, data, 1);
		if (ft_strncmp(line, value, ft_strlen(value)) == 0 && ft_strlen(line) == ft_strlen(value))
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, fd);
		free(line);
	}
	set_signals_noninteractive();
	close(fd);
}

t_pars_err	pars_create_heredoc(t_list	*cmds, char *value, t_shell_data *data)
{
	t_command		*command;
	static size_t	next_heredoc_code = 0;
	char			*filename;
	char			*tmp;

	command = (t_command *) ft_lstlast(cmds)->content;
	tmp = ft_itoa(next_heredoc_code++);
	if (!tmp)
		return (PARS_MALLOC_ERROR);
	filename = ft_strjoin("/tmp/.minishel_heredoc_", tmp);
	free(tmp);
	if (!filename)
		return (PARS_MALLOC_ERROR);
	read_heredoc(open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666),
		value, data);
	command->fd_in = open(filename, O_RDONLY, 0666);
	free(filename);
	return (PARS_NO_ERROR);
}
