/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 19:43:41 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/20 00:16:43 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Converts string of characters to integer.

	In the first loop we only handle characters considered "blank spaces",
	ASCII chars from 0-7 contains control chars like NUL, BEL, etc.

	1. str[pos] - '0' this converts a character into its corresponding numeric
	value.
		-'0' is 48 and '2' is 50. So substracting '0' from a char like '2' will
		give you the actual integer value 2.

	2. (result * 10) makes room for the next digit to add up.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	pos;

	sign = 1;
	result = 0;
	pos = 0;
	while (str[pos] == ' ' || str[pos] == '\f' || str[pos] == '\n'
		|| str[pos] == '\r' || str[pos] == '\t' || str[pos] == '\v')
		pos++;
	if (str[pos] == '-' || str[pos] == '+')
	{
		if (str[pos] == '-')
			sign *= -1;
		pos++;
	}
	while (str[pos] >= '0' && str[pos] <= '9')
	{
		result = (result * 10) + (str[pos] - '0');
		pos++;
	}
	return (result * sign);
}

// int	main(void)
// {
// 	char *str = "       -2342342";
// 	printf("%d\n", ft_atoi(str));
// 	return (0);
// }
