/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_pointer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:53:28 by yaperalt          #+#    #+#             */
/*   Updated: 2024/12/11 11:55:13 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_aux_pointer(unsigned long long ptr)
{
	unsigned long long int	len;

	len = 0;
	if (!ptr)
		return (write(1, "(nil)", 5));
	len += write(1, "0x", 2);
	len += ft_aux_hex(ptr, 'x');
	return (len);
}

// int	main(void)
// {
// 	int	x;
// 	int	*ptr;

// 	x = 42;
// 	ptr = NULL;
// 	ft_aux_pointer((unsigned long)ptr);
// 	ft_aux_pointer((unsigned long)&x);
// 	return (0);
// }
