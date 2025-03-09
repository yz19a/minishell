/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:07:12 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/14 06:22:42 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memset fucntion fills the first n bytes of the memory are pointed to
	by str with the constant byte c.

	c is a paramater type int that converts it to unsigned char before
	using it to fill a block of memory.

	void *str type allows for passing any kind of data,
	could point to an array of any type.

	Error:
	I replaced char *str = "hola buenas tardes"; with
	char str[] = "hola buenas tardes";. This creates a modifiable array
	instead of pointing to a string literal.
*/

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*p;
	size_t			count;

	c = (unsigned char)c;
	p = (unsigned char *)str;
	count = 0;
	while (count < n)
	{
		p[count] = c;
		count++;
	}
	return (str);
}

// int	main(void)
// {
// 	char str[] = "hola buenas tardes";
// 	int c = 36;
// 	printf("%p\n", ft_memset(str, c, 5));
// 	printf("%s\n", str);
// }
