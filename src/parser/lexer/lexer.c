/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:30:39 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/09 17:49:36 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Función de transición a partir de estado y símbolo actual
t_lex_st	lex_next_state(t_lex_st state, char cur_char)
{
	// Si estamos entre comillas simples o dobles y se cierran
	// volvemos al estado LEX_WORD, si estamos en el estado inicial
	// y el símbolo actual no es ninguno de los especiales pasamos a LEX_WORD
	if ((state == LEX_SIMPLE_QUOTE && cur_char == '\'')
		|| (state == LEX_DOUBLE_QUOTE && cur_char == '"')
		|| (state == LEX_START && !ft_strchr("<' |\">", cur_char)))
		return (LEX_WORD);
	// Si estamos en LEX_START o LEX_WORD y encontramos una comilla simple
	// pasamos a LEX_SIMPLE_QUOTE para indicar que hemos visto una '
	else if ((state == LEX_START && cur_char == '\'')
		|| (state == LEX_WORD && cur_char == '\''))
		return (LEX_SIMPLE_QUOTE);
	// Si estamos en LEX_START o LEX_WORD y encontramos una comilla doble
	// pasamos a LEX_SIMPLE_QUOTE para indicar que hemos visto una "
	else if ((state == LEX_START && cur_char == '"')
		|| (state == LEX_WORD && cur_char == '"'))
		return (LEX_DOUBLE_QUOTE);
	// Si estamos en LEX_WORD y encontramos alguno de < | > pasamos a
	// estado inicial de nuevo
	else if ((state == LEX_WORD && ft_strchr("< |>", cur_char)))
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
	// Si se quedan sin cerrar comillas devolver error
	if (state == LEX_SIMPLE_QUOTE || state == LEX_DOUBLE_QUOTE)
	{
		print_error("lexer", "syntax error", "quote not closed", 0);
		return (lex_free_token_list(&tokens), (t_list *) 0);
	}
	return (tokens);
}