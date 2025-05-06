/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:30:39 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/06 11:34:16 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*lexer(char *command, t_shell_data *data)
{
	t_lex_st	state;
	t_list		*tokens;

	(void) data;
	state = LEX_START;
	tokens = 0;
	if (!command)
		return (0);
	while (*command)
	{
		if (state == LEX_START)
			lex_start_state(&command, &state, &tokens);
		else if (state == LEX_SIMPLE_QUOTE)
			lex_quote_states(&command, &state, &tokens, '\'');
		else if (state == LEX_DOUBLE_QUOTE)
			lex_quote_states(&command, &state, &tokens, '"');
		else if (state == LEX_WORD)
			lex_word_state(&command, &state, &tokens);
	}
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE)
	{
		print_error("lexer", "syntax error", "quote not closed", 0);
		return (lex_free_token_list(&tokens), (t_list *) 0);
	}
	return (tokens);
}