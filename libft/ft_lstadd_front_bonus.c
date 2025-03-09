/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 18:54:25 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/26 14:43:24 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	This function is designed to add a new node at the front of a linked list.
	t_list **lst	this is a pointer to the first element of the list.
	t_list *new		this is a pointer to the new node to be added.
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	new->next = *lst;
	*lst = new;
}
