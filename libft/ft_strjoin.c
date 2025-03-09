/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 03:52:48 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/20 00:39:15 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a new
	string, which is the result of the concatenation
	of ’s1’ and ’s2’.
*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*strjoin;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc(sizeof(char) * (len + 1));
	if (!strjoin)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
		strjoin[j++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		strjoin[j++] = s2[i++];
	strjoin[j] = '\0';
	return (strjoin);
}

// int	main(void)
// {
// 	char *s1 = "hola, ";
// 	char *s2 = "eres tonto?";
// 	printf("%s\n", ft_strjoin(s1, s2));
// }
