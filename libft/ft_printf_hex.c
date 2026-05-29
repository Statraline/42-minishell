/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:39 by srichard          #+#    #+#             */
/*   Updated: 2025/11/27 15:23:44 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_hex(unsigned int n, const char format)
{
	int	len;

	len = 0;
	if (n >= 16)
		len += ft_printf_hex(n / 16, format);
	if (format == 'x')
		ft_putchar_fd("0123456789abcdef"[n % 16], 1);
	else if (format == 'X')
		ft_putchar_fd("0123456789ABCDEF"[n % 16], 1);
	len++;
	return (len);
}
