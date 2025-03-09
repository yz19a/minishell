/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 22:10:07 by yaperalt          #+#    #+#             */
/*   Updated: 2024/12/25 22:19:03 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

// int main() {
//     const char *s1 = "hello";
//     const char *s2 = "hello";
//     const char *s3 = "world";
//     const char *s4 = "hell";

//     printf("ft_strcmp(s1, s2) = %d\n", ft_strcmp(s1, s2));
//     printf("ft_strcmp(s1, s3) = %d\n", ft_strcmp(s1, s3));
//     printf("ft_strcmp(s1, s4) = %d\n", ft_strcmp(s1, s4));

//     return 0;
// }
