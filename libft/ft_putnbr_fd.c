/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 06:06:10 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/20 00:21:12 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	First Call: ft_putnbr_fd(214214, fd)
	The number that the function receives is 214214. Since 214214 >= 10,
	it divides:
	214214 / 10 = 21421 (integer part of the division).
	214214 % 10 = 4 (remainder of the division, which is the last digit).
	It recursively calls ft_putnbr_fd(21421, fd) to process the remainder of the
	number, and the digit 4 will be printed after all calls are finished.
	...
	Sixth Call: Prints 2.
	Fifth Call: Now prints the 1 that was pending.
	Fourth Call: Now prints the 4 that was pending.
	Third Call: Now prints the 2.
	Second Call: Now prints the 1.
	First Call: Finally, prints the 4.
*/

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
		ft_putchar_fd(n + '0', fd);
}
