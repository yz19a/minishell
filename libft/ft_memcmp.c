/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 21:43:18 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/17 02:21:37 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The memcmp() function compares the first n bytes (each interpreted as un‐
    signed char) of the memory areas s1 and s2, until it finds a difference and
	then returns the remainder of the two

*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*p_s1;
	unsigned char	*p_s2;
	size_t			i;

	p_s1 = (unsigned char *)s1;
	p_s2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (p_s1[i] != p_s2[i])
			return (p_s1[i] - p_s2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	*s1 = "\0hola 0";
// 	char	*s2 = "\0hola 1";
// 	printf("%d\n", ft_memcmp(s1, s2, 7));
// }
