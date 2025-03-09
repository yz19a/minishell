/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:45:08 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 00:06:59 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Strlcpy is a function in C used for copying strings with a size limit to
	prevent buffer overflows, it is designed to be a safer alternative to
	functions like strcpy.

	It purpose is to safely copy src into dst making sure it is null-terminated.
	Making sure too that the string fits within a give size.

	if (size == 0)
		return (srclen);	No space to copy so we end it there.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	srclen;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
		return (srclen);
	while (src[i] != '\0' && (i < (size - 1)))
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (srclen);
}

/*
int	main(void)
{
	char	dest[6];
	char	*src = "hola buenas";

	printf("%zu\n", ft_strlcpy(dest, src, sizeof(dest)));
	printf("%s\n", dest);
}
*/
