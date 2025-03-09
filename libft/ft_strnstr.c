/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 22:28:42 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/17 02:01:53 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	The  strnstr()  function  locates the first occurrence of the null-termi‐
    nated string little in the string big, where not more than len characters
    are searched.  Characters that appear after  a  ‘\0’  character  are  not
    searched.

	If little is empty, big is returned.
	If little occurs nowhere in big, NULL is returned.
	Otherwise, a pointer to the first character of the first ocurrence of little
	is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(little) == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < n)
	{
		j = 0;
		if (big[i] == little[0])
		{
			while (little[j] != '\0' && big[i + j] == little[j] && (i + j) < n)
				j++;
			if (little[j] == '\0')
				return ((char *)&big[i]);
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	char str[] = "hola buenas tardes";
// 	char to_find[] = "tardes";
// 	printf("%p\n", ft_strnstr(str, to_find, 17));
// }
