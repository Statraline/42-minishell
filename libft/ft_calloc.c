/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:18:49 by srichard          #+#    #+#             */
/*   Updated: 2025/11/14 13:53:26 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t number, size_t size)
{
	unsigned char	*tmp;
	size_t			i;
	size_t			total_size;

	total_size = number * size;
	if (size != 0 && total_size / size != number)
		return (NULL);
	i = 0;
	tmp = malloc(total_size);
	if (!tmp)
		return (NULL);
	while (i < total_size)
		tmp[i++] = 0;
	return (tmp);
}
