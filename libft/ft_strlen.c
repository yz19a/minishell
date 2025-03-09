/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:47:59 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/16 00:08:25 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

	The  strlen() function calculates the length of the string pointed to by
    s, excluding the terminating null byte ('\0').

	size_t stands for size type, it is an unsigned int.
	It is platform dependent(32-bit system(4 bytes) 64-bit system(8 bytes))
	,used in functions with memory allocation.

	Why use it?
	1. You can handle very large strings in systems where maximum possible
	string length is large.
	2. You avoid negative values.
*/

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

/*
int main()
{
	char *str = "hola";

	printf("%ld\n", ft_strlen(str));
}
*/
