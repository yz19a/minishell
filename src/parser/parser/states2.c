/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:12:51 by jalcausa          #+#    #+#             */
/*   Updated: 2025/06/08 17:20:34 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars_err	pars_redheredoc_st(
	t_list *tokens,
	t_pars_st *state,
	t_list **cmds,
	t_shell_data *data
) {
	t_token		*token;
	t_pars_err	result;

	token = (t_token *) tokens->content;
	*state = pars_next_state(*state, (t_token *) tokens->content);
	if (token->type == TOK_WORD)
	{
		result = pars_create_heredoc(*cmds, token->value, data);
		if (result == PARS_NO_ERROR && g_exit_status == 130)
			return (PARS_CANCELLED);
		return (result);
	}
	if (token->type == TOK_PIPE)
		return (PARS_SYNTAX_ERROR);
	return (PARS_NO_ERROR);
}

t_pars_err	pars_invalid_st(t_list *tokens, t_pars_st *state)
{
	*state = pars_next_state(*state, (t_token *) tokens->content);
	return (PARS_SYNTAX_ERROR);
}
