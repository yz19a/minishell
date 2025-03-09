/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:11:19 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/20 03:01:48 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns a copy of
	’s1’ with the characters specified in ’set’ removed
	from the beginning and the end of the string.
*/

#include "libft.h"

static int	ft_is_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s1_trimmed;
	size_t	start;
	size_t	end;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_is_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	if (start == end)
		return (ft_strdup(""));
	while (end > start && ft_is_in_set(s1[end - 1], set))
		end--;
	s1_trimmed = malloc(sizeof(char) * ((end - start) + 1));
	if (!s1_trimmed)
		return (NULL);
	ft_memcpy(s1_trimmed, &s1[start], (end - start));
	s1_trimmed[end - start] = '\0';
	return (s1_trimmed);
}

// int	main(void)
// {
// 	char *s1 = "321ho123la123";
// 	char *set = "3";
// 	printf("%s\n", ft_strtrim(s1, set));
// }
