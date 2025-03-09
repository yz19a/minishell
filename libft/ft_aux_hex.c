/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:53:25 by yaperalt          #+#    #+#             */
/*   Updated: 2024/12/11 11:55:05 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_aux_hex(unsigned long long n, char hexa)
{
	unsigned long long	len;

	len = 0;
	if (n >= 16)
		len += ft_aux_hex(n / 16, hexa);
	if (hexa == 'x')
		len += ft_putchar("0123456789abcdef"[n % 16]);
	else if (hexa == 'X')
		len += ft_putchar("0123456789ABCDEF"[n % 16]);
	return (len);
}

// int	main(void)
// {
// 	ft_aux_hex(12313123, 1);
// 	write(1, "\n", 1);
// 	return (0);
// }
