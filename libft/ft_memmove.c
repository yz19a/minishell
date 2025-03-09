/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 06:17:40 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 19:44:50 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memmove() function copies n bytes from memory area src to memory area
	dest.  The memory  areas  may overlap: copying takes place as though the
	bytes in src are first copied into a temporary array that does not overlap
	src or dest, and the  bytes  are then copied from the temporary array to
	dest.

	unsigned char *src_p: A pointer to the source memory area, cast to
	unsigned char * so that the memory can be manipulated byte by byte.

	dest_p > src_p: This means the destination memory block begins after the
	source in memory, which risks overwriting the source data during copying if
	we proceed in a forward direction.

	Memory (str):
	+---+---+---+---+---+---+---+---+---+---+---+----+
	| y | a | n | e | l |   | y | a | n | e | l | \0 |
	+---+---+---+---+---+---+---+---+---+---+---+----+

	str + 2 points to the third character in the string, i.e., 'n'

	ft_memmove(str, str + 5, 3 * sizeof(char));
	We want to move 3 characters (3 * sizeof(char) = 3 bytes) from the
	position starting at str + 2 (i.e., the substring "nel") to the start
	of str.
*/

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_p;
	unsigned char	*dest_p;

	i = 0;
	if (!dest && !src)
		return (0);
	src_p = (unsigned char *)src;
	dest_p = (unsigned char *)dest;
	if (dest_p > src_p)
		while (n-- != 0)
			dest_p[n] = src_p[n];
	else
	{
		while (i < n)
		{
			dest_p[i] = src_p[i];
			i++;
		}
	}
	return (dest);
}

// int	main(void)
// {
// 	char	str[] = "yanel yanel";
// 	printf("%s\n", str);
// 	ft_memmove(str, str + 3, 5 * sizeof(char));
// 	printf("%s\n", str);
// 	return (0);
// }
