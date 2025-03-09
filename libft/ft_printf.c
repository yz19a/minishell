/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 14:47:38 by yaperalt          #+#    #+#             */
/*   Updated: 2024/12/11 11:55:33 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	handle_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 'i' || c == 'd')
		return (ft_aux_putnbr(va_arg(args, int)));
	if (c == 's')
		return (ft_aux_string(va_arg(args, char *)));
	if (c == 'p')
		return (ft_aux_pointer(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_aux_hex(va_arg(args, unsigned int), 'x'));
	if (c == 'X')
		return (ft_aux_hex(va_arg(args, unsigned int), 'X'));
	if (c == 'u')
		return (ft_aux_unsigned(va_arg(args, unsigned int)));
	if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_printed_chars;

	total_printed_chars = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			total_printed_chars += handle_format(*format, args);
		}
		else
			total_printed_chars += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (total_printed_chars);
}
