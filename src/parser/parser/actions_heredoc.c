/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:18:13 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/08 16:22:27 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_heredoc_sigint(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	exit(1);
}

static void	read_heredoc(int fd, char *value, t_shell_data *data)
{
	char	*line;

	signal(SIGINT, handle_heredoc_sigint);
	while (1)
	{
		line = readline(" >> ");
		if (!line)
		{
			printf("\n");
			break;
		}
		expand_variables(&line, data, 1);
		if (ft_strncmp(line, value, ft_strlen(value)) == 0 && \
			ft_strlen(line) == ft_strlen(value))
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

static int	child_heredoc(char *filename, char *value, t_shell_data *data)
{
	int		status;
	pid_t	pid;
	
	pid = fork();
	if (pid == 0)
	{
		read_heredoc(open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666),
			value, data);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		free(filename);
		return (1);
	}
	return (0);
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
	if (child_heredoc(filename, value, data) == 1)
		return (PARS_MALLOC_ERROR);
	command->fd_in = open(filename, O_RDONLY, 0666);
	free(filename);
	return (PARS_NO_ERROR);
}
