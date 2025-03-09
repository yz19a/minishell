/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:53:36 by yaperalt          #+#    #+#             */
/*   Updated: 2024/12/11 11:55:24 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Example:
	If n = 123, this function will:
	Call ft_aux_unsigned(12).
	Call ft_aux_unsigned(1).
	Print '1' and return 1.
	Print '2' and return 1 + 1 = 2.
	Print '3' and return 2 + 1 = 3.
	So the total number of characters printed will be 3, and the function
	will return 3.
*/
int	ft_aux_unsigned(unsigned long int n)
{
	int	i;

	i = 0;
	if (n > 9)
	{
		i += ft_aux_unsigned(n / 10);
	}
	return (i += ft_putchar(n % 10 + '0'));
}
