/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaperalt <yaperalt@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 05:45:55 by yaperalt          #+#    #+#             */
/*   Updated: 2024/09/17 05:52:07 by yaperalt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Like a regular ft_putchar but we pick the fd of our choice.

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
