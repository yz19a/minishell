/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalcausa <jalcausa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 22:25:42 by jalcausa          #+#    #+#             */
/*   Updated: 2025/05/19 20:31:48 by jalcausa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Crea un nuevo token del tipo indicado con contenido indicado
t_list	*lex_create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	token->type = type;
	token->value = value;
	token->var_name = ft_strdup("");
	return (ft_lstnew(token));
}

// Añade un símbolo al contenido del último token de la lista
void	append_last_token(t_list **tokens, char **cmd)
{
	t_token	*token;
	char	*substr;
	char	*aux;

	token = ft_lstlast(*tokens)->content;
	substr = ft_substr(*cmd, 0, 1);
	aux = ft_strjoin(token->value, substr);
	free(substr);
	free(token->value);
	token->value = aux;
}

static void	free_token(void *token)
{
	t_token	*t;

	t = (t_token *) token;
	if (!token)
		return ;
	if (t->value)
		free(t->value);
	if (t->var_name)
		free(t->var_name);
	free(t);
}

void	lex_free_token_list(t_list **lst)
{
	if (!lst)
		return ;
	ft_lstclear(lst, &free_token);
}