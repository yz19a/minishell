/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 00:55:24 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 05:32:34 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Memcpy is used to copy a block of memory from one location to another.
	Unlike other copy functions, the memcpy function copies the specified number
	of bytes from one memory location to the other memory location regardless of
	the type of data stored.

	if (!dst && !src) Verify if both of those pointer are null.
	When a pointer is null means that does not point to any valid address
	in memory.

	dest[count] != '\0' && src[count] != '\0' This verifies the values not the
	validity.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*dest_aux;
	const unsigned char	*src_aux;
	size_t				count;

	dest_aux = (unsigned char *)dest;
	src_aux = (const unsigned char *)src;
	count = 0;
	if (!dest && !src)
		return (0);
	while (count < n)
	{
		dest_aux[count] = src_aux[count];
		count++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	dest[50];
// 	char	src[50] = "Hello my name is Jeff.";

// 	ft_memcpy(dest, src, 5);
// 	printf("Source: %s\n", src);
// 	printf("Destination after ft_memcpy: %s\n", dest);
// }
