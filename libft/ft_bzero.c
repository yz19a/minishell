/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 05:53:02 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 04:50:35 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	bzero is a function that erases the data in the n bytes of the memory
	starting at the location pointed to by s, by writing zeros
	(bytes containing '\0') to that area. (Man definition)

	if try to print str after calling ft_bzero with str as parameter, it will
	only print until the first null character it encounters.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			count;
	unsigned char	*s2;

	count = 0;
	s2 = (unsigned char *)s;
	while (count < n)
	{
		s2[count] = '\0';
		count++;
	}
}

// int	main(void)
// {
// 	char str[] = "hola buenas tardes";
// 	ft_bzero(str, 1);
// 	size_t i;
// 	i = 0;
// 	while (i < sizeof(str))
// 	{
// 		if (str[i] == '\0')
// 			printf("\\0");
// 		else
// 			printf("%c", str[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }
