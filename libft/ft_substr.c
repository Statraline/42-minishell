/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:19:15 by srichard          #+#    #+#             */
/*   Updated: 2025/11/14 13:56:26 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *src, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!src)
		return (NULL);
	if (start > ft_strlen(src))
		return (ft_strdup(""));
	if (len > ft_strlen(src + start))
		len = ft_strlen(src + start);
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = src[start + i];
		i++;
	}
	return (str);
}
