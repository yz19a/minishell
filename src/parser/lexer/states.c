/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:36:07 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/08 22:44:12 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lex_quote_states(char **line, t_lex_st *st, t_list **res, char quote)
{
	// Actualiza estado al que pasamos tras leer la comilla
	// y actualiza la lista de tokens para incluir el símbolo actual como
	// nuevo token hasta que se cierren
	*st = lex_next_state(*st, **line);
	if (quote == '"')
	{
		if (!ft_strchr("\"", **line))
			append_last_token(res, line);
	}
	else
	{
		if (**line != '\'')
			append_last_token(res, line);
	}
	(*line)++;
}

void	lex_word_state(char **line, t_lex_st *st, t_list **res)
{
	// Actualiza estado al que pasamos tras leer el símbolo actual
	// Actualiza estado al que pasamos tras leer el símbolo actual
	// y actualiza la lista de tokens para incluir el símbolo actual como
	// nuevo token o añadirlo a uno existente
	*st = lex_next_state(*st, **line);
	if (**line == '|')
		ft_lstadd_back(res, lex_create_token(TOK_PIPE, 0));
	else if (**line == '>' && *((*line) + 1) == '>')
	{
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT_APPEND, 0));
		(*line)++;
	}
	else if (**line == '>')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT, 0));
	else if (**line == '<' && *((*line) + 1) == '<')
	{
		ft_lstadd_back(res, lex_create_token(TOK_HDOC, 0));
		(*line)++;
	}
	else if (**line == '<')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_IN, 0));
	else if (!ft_strchr(" '\"", **line))
		append_last_token(res, line);
	(*line)++;
}

void	lex_start_state(char **line, t_lex_st *state, t_list **res)
{
	// Actualiza estado al que pasamos tras leer el símbolo actual
	// partiendo del estado inicial, aquí siempre hay que crear un
	// nuevo token
	*state = lex_next_state(*state, **line);
	if (ft_strchr("'\"", **line))
		ft_lstadd_back(res, lex_create_token(TOK_WORD, ft_strdup("")));
	else if (**line == '|')
		ft_lstadd_back(res, lex_create_token(TOK_PIPE, 0));
	else if (**line == '>' && *((*line) + 1) == '>')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT_APPEND, 0));
	else if (**line == '>')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_OUT, 0));
	else if (**line == '<' && *((*line) + 1) == '<')
		ft_lstadd_back(res, lex_create_token(TOK_HDOC, 0));
	else if (**line == '<')
		ft_lstadd_back(res, lex_create_token(TOK_REDIR_IN, 0));
	else if (**line == ' ')
		;
	else
		ft_lstadd_back(res, lex_create_token(TOK_WORD,
				ft_substr(*line, 0, 1)));
	if ((**line == '>' && *((*line) + 1) == '>')
		|| (**line == '<' && *((*line) + 1) == '<'))
		(*line)++;
	(*line)++;
}
