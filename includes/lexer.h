/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:08:12 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/26 13:37:33 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum e_lexer_state
{
	LEX_START,
	LEX_SIMPLE_QUOTE,
	LEX_DOUBLE_QUOTE,
	LEX_WORD
}	t_lex_st;

typedef enum e_token_type
{
	TOK_WORD,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_REDIR_OUT_APPEND,
	TOK_HDOC,
	TOK_PIPE
}	t_token_type;

typedef struct s_token
{
	char			*value;
	char			*var_name;
	t_token_type	type;
}	t_token;

#endif
