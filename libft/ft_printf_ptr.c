/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:20:23 by srichard          #+#    #+#             */
/*   Updated: 2025/11/27 15:27:34 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptr_len(unsigned long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num != 0)
	{
		len++;
		num = num / 16;
	}
	return (len);
}

static void	ft_put_ptr(unsigned long num)
{
	if (num >= 16)
	{
		ft_put_ptr(num / 16);
		ft_put_ptr(num % 16);
	}
	else
	{
		ft_putchar_fd("0123456789abcdef"[num], 1);
	}
}

int	ft_printf_ptr(void *ptr)
{
	unsigned long	addr;

	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	ft_put_ptr(addr);
	return (ft_ptr_len(addr) + 2);
}
