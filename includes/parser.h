/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 23:14:16 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/26 13:37:40 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_parser_state
{
	PARS_START,
	PARS_COMMAND,
	PARS_REDIR_IN,
	PARS_REDIR_OUT,
	PARS_REDIR_OUT_APPEND,
	PARS_REDIR_IN_HEREDOC,
	PARS_INVALID
}	t_pars_st;

typedef enum e_parser_error
{
	PARS_NO_ERROR,
	PARS_SYNTAX_ERROR,
	PARS_MALLOC_ERROR,
	PARS_NO_SUCH_FILE_OR_DIR,
}	t_pars_err;

#endif
