/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 04:06:24 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/27 17:38:44 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The  calloc() function allocates memory for an array of num elements of
	size bytes each and returns a pointer to the allocated memory.  The memory
	is set to zero.   If num  or  size is 0, then calloc() returns a unique
	pointer value that can later be successfully passed to free().

	size_t num: The number of elements to allocate.
	size_t size: The size (in bytes) of each element.

	Block  of memory would be allocated:
     malloc(num * size);
*/

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*s;

	s = (void *)malloc(num * size);
	if (!s)
		return (NULL);
	ft_bzero(s, (num * size));
	return (s);
}
