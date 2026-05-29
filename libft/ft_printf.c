/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:18:31 by srichard          #+#    #+#             */
/*   Updated: 2025/11/27 15:45:10 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		count;

	va_start(args, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			count += ft_formats(args, *str);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			count++;
		}
		str++;
	}
	va_end(args);
	return (count);
}

int	ft_formats(va_list args, const char format)
{
	int	count;

	count = 0;
	if (format == 'c')
		count += ft_printf_char(va_arg(args, int));
	else if (format == 's')
		count += ft_printf_str(va_arg(args, char *));
	else if (format == 'p')
		count += ft_printf_ptr(va_arg(args, void *));
	else if (format == 'd' || format == 'i')
		count += ft_printf_nbr(va_arg(args, int));
	else if (format == 'u')
		count += ft_printf_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		count += ft_printf_hex(va_arg(args, unsigned int), format);
	else if (format == '%')
		count += ft_printf_percent();
	return (count);
}
