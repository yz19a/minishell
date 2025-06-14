/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:01:33 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/08 17:36:16 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pars_print_error(t_pars_st state, t_pars_err err)
{
	if (err == PARS_MALLOC_ERROR)
		print_error("parser", 0, "memory error", 0);
	else if (err == PARS_NO_SUCH_FILE_OR_DIR)
		print_error("parser", 0, "no such file or directory", 0);
	else if (err == PARS_CANCELLED)
		return ;
	else if (state != PARS_COMMAND || err == PARS_SYNTAX_ERROR)
		print_error("parser", 0, "syntax error", 0);
}

static void	set_pipes(t_list *instr)
{
	t_command	*cmd;
	t_command	*next;
	int			pipes[2];

	while (instr)
	{
		cmd = (t_command *) instr->content;
		if (instr->next)
		{
			next = (t_command *) instr->next->content;
			pipe(pipes);
			if (cmd->fd_out == 0)
				ft_memcpy(&(cmd->fd_out), pipes + 1, sizeof(int));
			else
				close(pipes[1]);
			if (next->fd_in == 0)
				ft_memcpy(&(next->fd_in), pipes + 0, sizeof(int));
			else
				close(pipes[0]);
		}
		instr = instr->next;
	}
}

static t_pars_err	pars_states(
	t_list *tokens,
	t_pars_st *st,
	t_list **cmds,
	t_shell_data *data
) {
	t_pars_err	err;

	err = PARS_SYNTAX_ERROR;
	if (*st == PARS_START)
		err = pars_start_st(tokens, st, cmds);
	else if (*st == PARS_COMMAND)
		err = pars_command_st(tokens, st, cmds);
	else if (*st == PARS_REDIR_IN)
		err = pars_redirin_st(tokens, st, cmds);
	else if (*st == PARS_REDIR_OUT)
		err = pars_redirout_st(tokens, st, cmds);
	else if (*st == PARS_REDIR_OUT_APPEND)
		err = pars_rediroappe_st(tokens, st, cmds);
	else if (*st == PARS_REDIR_IN_HEREDOC)
		err = pars_redheredoc_st(tokens, st, cmds, data);
	else if (*st == PARS_INVALID)
		err = pars_invalid_st(tokens, st);
	return (err);
}

t_pars_st	pars_next_state(t_pars_st st, t_token *tok)
{
	if (st == PARS_COMMAND && tok->type == TOK_PIPE)
		return (PARS_START);
	else if ((st == PARS_START && tok->type == TOK_PIPE)
		|| ((st == PARS_REDIR_IN || st == PARS_REDIR_IN_HEREDOC
				|| st == PARS_REDIR_OUT || st == PARS_REDIR_OUT_APPEND)
			&& tok->type != TOK_WORD))
		return (PARS_INVALID);
	else if ((st == PARS_START && tok->type == TOK_WORD)
		|| ((st == PARS_REDIR_IN || st == PARS_REDIR_IN_HEREDOC
				|| st == PARS_REDIR_OUT || st == PARS_REDIR_OUT_APPEND)
			&& tok->type == TOK_WORD))
		return (PARS_COMMAND);
	else if ((st == PARS_START && tok->type == TOK_REDIR_IN)
		|| (st == PARS_COMMAND && tok->type == TOK_REDIR_IN))
		return (PARS_REDIR_IN);
	else if ((st == PARS_START || st == PARS_COMMAND) && tok->type == TOK_HDOC)
		return (PARS_REDIR_IN_HEREDOC);
	else if ((st == PARS_START && tok->type == TOK_REDIR_OUT)
		|| (st == PARS_COMMAND && tok->type == TOK_REDIR_OUT))
		return (PARS_REDIR_OUT);
	else if ((st == PARS_START && tok->type == TOK_REDIR_OUT_APPEND)
		|| (st == PARS_COMMAND && tok->type == TOK_REDIR_OUT_APPEND))
		return (PARS_REDIR_OUT_APPEND);
	return (st);
}

t_list	*parser(t_list *tokens, t_shell_data *data)
{
	t_pars_st	state;
	t_list		*commands;
	t_pars_err	err;

	commands = 0;
	state = PARS_START;
	err = PARS_NO_ERROR;
	while (tokens && err == PARS_NO_ERROR)
	{
		err = pars_states(tokens, &state, &commands, data);
		if (err == PARS_CANCELLED)
			break ;
		tokens = tokens->next;
	}
	pars_print_error(state, err);
	if ((err != PARS_NO_ERROR || state != PARS_COMMAND)
		&& err == PARS_CANCELLED)
	{
		pars_free_command_list(&commands);
		return ((t_list *) 0);
	}
	if (err != PARS_NO_ERROR || state != PARS_COMMAND)
		return (pars_free_command_list(&commands), (t_list *) 0);
	set_pipes(commands);
	return (commands);
}
