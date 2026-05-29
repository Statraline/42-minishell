/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:19:53 by srichard          #+#    #+#             */
/*   Updated: 2025/11/27 15:24:25 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_nbr(int n)
{
	long	nb;
	int		len;
	char	c;

	len = 0;
	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		len++;
		nb = -nb;
	}
	if (nb >= 10)
		len += ft_printf_nbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
	len++;
	return (len);
}
