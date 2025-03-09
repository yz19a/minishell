/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 04:18:52 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/24 00:34:19 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Allocates (with malloc(3)) and returns an array
	of strings obtained by splitting ’s’ using the
	character ’c’ as a delimiter. The array must end
	with a NULL pointer.
*/

#include "libft.h"

static int	ft_count_words(const char *s, char c)
{
	int	word_counter;

	word_counter = 0;
	while (*s)
	{
		if (*s != c)
		{
			word_counter++;
			while (*s != c && *s)
				s++;
		}
		else
			s++;
	}
	return (word_counter);
}

static char	**free_array(char **split, size_t i)
{
	while (i > 0)
		free(split[--i]);
	free(split);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	len;
	int		i;

	split = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (!split)
		return (NULL);
	i = 0;
	while (*s)
	{
		len = 0;
		if (*s != c)
		{
			while (s[len] && s[len] != c)
				len++;
			split[i++] = ft_substr(s, 0, len);
			if (!split[i - 1])
				return (free_array(split, i));
			s += len;
		}
		else
			s++;
	}
	split[i] = NULL;
	return (split);
}

// int	main(void)
// {
// 	char	*str;
// 	char	**split;
// 	int		i;

// 	str = "hola/chola/chola/chola";
// 	split = ft_split(str, '/');
// 	if (split)
// 	{
// 		i = 0;
// 		while (split[i] != NULL)
// 		{
// 			printf("%s\n", split[i]);
// 			i++;
// 		}
// 		i = 0;
// 		while (split[i] != NULL)
// 			free(split[i++]);
// 		free(split);
// 	}
// 	return (0);
// }
