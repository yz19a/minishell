/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:06:00 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 00:09:37 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strcmp() function compares the two strings s1 and s2.  The locale is
    not  taken into account (for a locale-aware comparison, see strcoll(3)).
    The comparison is done using unsigned characters. Returns an integer.

	unsigned char in return makes sure that all the char comparations
	are made between the positive values 0 and 255 and not between -128 and 127.
	Else if, we use signed char it could cause some problems when comparing
	negative values.

	Example:
	unsigned character:

	\xFF (only in hexadecimal it is 255) is interpreted as 255.
	\x00 (which is 0 in hexadecimal) is interpreted as 0.
	signed character:

	The string \xFF is interpreted as -1, because the binary value 11111111
	represents -1 in the back-end format, which is the standard representation
	of negative numbers in C.
	\x00 would still be 0.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t count)
{
	size_t	i;

	i = 0;
	if (count == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0'
		&& s1[i] == s2[i] && (i < count - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// int	main(void)
// {
// 	char	*s1;
// 	char	*s2;
// 	s1 = "hola buenasasdfs";
// 	s2 = "hola buenas x";
// 	printf("%d\n", ft_strncmp(s1, s2, 15));
// }
