/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 17:58:10 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/21 18:20:01 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a new node.
	The member variable ’content’ is initialized with
	the value of the parameter ’content’. The variable
	’next’ is initialized to NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

// int	main(void)
// {
// 	char 	*str = "hola buenas tardes";
// 	// Create a new node using ft_lstnew
//     t_list *node = ft_lstnew((void *)str);
//     // Check if the node was created successfully
//     if (node == NULL)
//     {
//         printf("Failed to allocate memory for the new node.\n");
//         return 1;
//     }
//     // Print the content of the node
//     printf("Node content: %s\n", (char *)node->content);
//     // Free the allocated memory for the node
//     free(node);
//     return 0;
// }
