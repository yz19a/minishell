/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 15:29:49 by yaperalt          #+#    #+#             */
/*   Updated: 2025/03/23 15:44:35 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTURES_H
# define MINISHELL_STRUCTURES_H

typedef struct s_signals
{
	bool builtin;
	bool heredoc;
} t_signals;

#endif