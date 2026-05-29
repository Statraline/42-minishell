/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:19:51 by srichard          #+#    #+#             */
/*   Updated: 2025/11/14 14:04:59 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_trim(const char *set, char c);
static char	*new_str(const char *s1, size_t start, size_t len);

char	*ft_strtrim(const char *s1, const char *set)
{
	int	i;
	int	j;

	if (!s1)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	i = 0;
	j = ft_strlen(s1) - 1 ;
	while (to_trim (set, s1[i]))
		i++;
	while (to_trim(set, s1[j]))
		j--;
	return (new_str(s1, i, j - (i - 1)));
}

static char	*new_str(const char *s1, size_t start, size_t len)
{
	char	*str;
	size_t	i;

	if (len <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	str = ft_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s1[start + i];
		i++;
	}
	return (str);
}

static int	to_trim(const char *set, char c)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
