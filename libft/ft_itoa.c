/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:32:44 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/18 21:35:36 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	itoa function converts a integer into a char *.
	static functions can only be used in the file they are in.
*/

#include "libft.h"

static size_t	ft_digit_counter(int n)
{
	size_t	counter;

	counter = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		counter++;
	while (n != 0)
	{
		n = n / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(int n)
{
	char		*result;
	long int	nlong;
	int			nlen;

	nlong = n;
	nlen = ft_digit_counter(nlong);
	result = malloc(sizeof(char) * (nlen + 1));
	if (!result)
		return (NULL);
	result[nlen] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		nlong = -nlong;
	}
	while (nlong > 0)
	{
		result[--nlen] = (nlong % 10) + '0';
		nlong = nlong / 10;
	}
	if (n == 0)
		result[0] = '0';
	return (result);
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(99999));
// }
