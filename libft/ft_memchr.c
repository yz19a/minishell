/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 05:22:25 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 05:42:52 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memchr() function scans the initial n bytes of the memory area pointed
	to by  s  for  the first instance of c.  Both c and the bytes of the memory
	area pointed to by s are interpreted as unsigned char.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*aux;
	size_t			i;

	aux = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (aux[i] == (unsigned char)c)
			return (&aux[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*str = "hola buenas \0 hola";
// 	char	s = 'u';

// 	printf ("%p\n", ft_memchr(str, s, 10));
// }
