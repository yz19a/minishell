/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 03:40:10 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 04:05:26 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The  strdup() function returns a pointer to a new string which is a
	duplicate of the string str.  Memory for the new string is obtained with
	malloc(3), and  can  be  freed with free(3).

	If malloc fails, it returns NULL.

	I used ft_strlcpy instead of a simplier manual copying loop, making the code
	easier to read. Strlcpy ensures the dest is always null-terminated if there
	is at least one byte in the destination buffer, also prevents buffer
	overflows in more complex scenarios.
*/

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	size_t	src_len;

	src_len = ft_strlen(src);
	dest = malloc(sizeof(char ) * (src_len + 1));
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, src, src_len + 1);
	return (dest);
}

// int	main(void)
// {
// 	char	*s = "hola buenas tardes, que tal";
// 	printf("%s\n", ft_strdup(s));
// }
