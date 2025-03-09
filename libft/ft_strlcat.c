/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 02:37:23 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/20 00:58:57 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	strlcat function concatenate strings, strlcat takes the full size of the
	buffer and guarantee to NUL-terminate(as long as there is at least one byte
	free in dest).

	n is the full length of the dest string you want to have, if dest length
	is smaller than n...
*/

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_size;
	size_t	src_size;
	size_t	i;
	size_t	total;

	i = 0;
	dest_size = ft_strlen(dest);
	src_size = ft_strlen(src);
	total = dest_size + src_size;
	if (size == 0)
		return (src_size);
	if (size <= dest_size)
		return (size + src_size);
	while (src[i] && dest_size < (size - 1))
		dest[dest_size++] = src[i++];
	dest[dest_size] = '\0';
	return (total);
}

// int	main(void)
// {
// 	char dest[] = "Hola, mi nombre es";
// 	char src[] = " Yanel";
// 	printf("%ld\n", ft_strlcat(dest, src, 25));
// 	printf("%s\n", dest);
// }
