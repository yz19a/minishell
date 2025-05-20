/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:18:09 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/19 20:12:16 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars_err	pars_start_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, token);
	if (token->type == TOK_WORD)
		return (pars_append_new_command(commands, token->value));
	if (token->type == TOK_REDIR_IN)
		return (pars_append_new_command(commands, 0));
	if (token->type == TOK_REDIR_OUT)
		return (pars_append_new_command(commands, 0));
	if (token->type == TOK_REDIR_OUT_APPEND)
		return (pars_append_new_command(commands, 0));
	if (token->type == TOK_HDOC)
		return (pars_append_new_command(commands, 0));
	if (token->type == TOK_PIPE)
		return (PARS_SYNTAX_ERROR);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_command_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, token);
	if (token->type == TOK_WORD)
		return (pars_append_arg_to_command(*commands, token->value));
	return (PARS_NO_ERROR);
}

t_pars_err	pars_redirin_st(t_list *tokens, t_pars_st *state, t_list **commands)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, (t_token *) tokens->content);
	if (token->type == TOK_WORD)
		return (pars_set_stdin(*commands, token->value));
	if (token->type == TOK_PIPE)
		return (PARS_SYNTAX_ERROR);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_redirout_st(t_list *tokens, t_pars_st *state, t_list **cmds)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, (t_token *) tokens->content);
	if (token->type == TOK_WORD)
		return (pars_set_stdout(*cmds, token->value, 0));
	if (token->type == TOK_PIPE)
		return (PARS_SYNTAX_ERROR);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_rediroappe_st(t_list *tokens, t_pars_st *state, t_list **cmds)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, (t_token *) tokens->content);
	if (token->type == TOK_WORD)
		return (pars_set_stdout(*cmds, token->value, 1));
	if (token->type == TOK_PIPE)
		return (PARS_SYNTAX_ERROR);
	return (PARS_NO_ERROR);
}
