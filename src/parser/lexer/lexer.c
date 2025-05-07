/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:30:39 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/07 09:03:37 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_st	lex_next_state(t_lex_st state, char line)
{
	// Si estamos entre comillas simples o dobles y se cierran
	// volvemos al estado LEX_WORD, si estamos en el estado inicial
	// y el símbolo actual no es ninguno de los especiales pasamos a LEX_WORD
	if ((state == LEX_SIMPLE_QUOTE && line == '\'')
		|| (state == LEX_DOUBLE_QUOTE && line == '"')
		|| (state == LEX_START && !ft_strchr("<' |\">", line)))
		return (LEX_WORD);
	else if ((state == LEX_START && line == '\'')
		|| (state == LEX_WORD && line == '\''))
		return (LEX_SIMPLE_QUOTE);
	else if ((state == LEX_START && line == '"')
		|| (state == LEX_WORD && line == '"'))
		return (LEX_DOUBLE_QUOTE);
	else if ((state == LEX_WORD && ft_strchr("< |>", line)))
		return (LEX_START);
	return (state);
}

t_list	*lexer(char *line, t_shell_data *data)
{
	t_lex_st	state;
	t_list		*tokens;

	(void) data;
	state = LEX_START;
	tokens = 0;
	if (!line)
		return (0);
	while (*line)
	{
		if (state == LEX_START)
			lex_start_state(&line, &state, &tokens);
		else if (state == LEX_SIMPLE_QUOTE)
			lex_quote_states(&line, &state, &tokens, '\'');
		else if (state == LEX_DOUBLE_QUOTE)
			lex_quote_states(&line, &state, &tokens, '"');
		else if (state == LEX_WORD)
			lex_word_state(&line, &state, &tokens);
	}
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE)
	{
		print_error("lexer", "syntax error", "quote not closed", 0);
		return (lex_free_token_list(&tokens), (t_list *) 0);
	}
	return (tokens);
}