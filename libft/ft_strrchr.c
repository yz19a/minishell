/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:46:16 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 20:15:28 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The strrchr() function returns a pointer to the last occurrence of the
	character c in the string s.
*/

#include "libft.h"

char	*ft_strrchr(const	char *str, int c)
{
	char	*aux;

	aux = 0;
	while (*str)
	{
		if (*str == (unsigned char )c)
			aux = (char *)str;
		str++;
	}
	if ((unsigned char )c == '\0')
		return ((char *)str);
	return (aux);
}

// int	main(void)
// {
// 	char	str[] = "hola buena tardes";
// 	char	*result = ft_strrchr(str, 's');

// 	if (result)
// 		printf("%s\n", result);
// 	else
// 		printf("Character not found.\n");
// 	return (0);
// }
