/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:49:23 by yaperalt          #+#    #+#             */
/*   Updated: 2024/12/11 11:55:16 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// This file contains the functions needed to print %d and %i.
// We use int as return value to verify/count the characters printed in the
// standard output
int	ft_aux_putnbr(int nb)
{
	int	i;

	i = 0;
	if (nb == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nb < 0)
	{
		i += ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		i += ft_aux_putnbr(nb / 10);
		i += ft_aux_putnbr(nb % 10);
	}
	else
		i += ft_putchar(nb + '0');
	return (i);
}

// int	main(void)
// {
// 	int	number;
// 	int	total;
// 	number = 42;
// 	total = ft_aux_putnbr(number);// return value is stored in total
// 	ft_putchar(' ');
// 	ft_aux_putnbr(total);// we print the value stored in total
// 	ft_putchar('\n');
// 	return (0);
// }
