/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:20:58 by srichard          #+#    #+#             */
/*   Updated: 2025/11/27 15:28:41 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_unsigned(unsigned int n)
{
	unsigned int	nb;
	int				len;
	char			c;

	len = 0;
	nb = n;
	if (nb >= 10)
		len += ft_printf_unsigned(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
	len++;
	return (len);
}
