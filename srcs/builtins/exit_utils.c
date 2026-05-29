/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 00:39:59 by remusung          #+#    #+#             */
/*   Updated: 2026/05/24 17:06:58 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Check if next digit causes overflow */
static int	check_overflow(long long res, int next_digit, int neg)
{
	if (neg == 1)
	{
		if (res > (LLONG_MAX - next_digit) / 10)
			return (1);
	}
	else
	{
		if (-res < (LLONG_MIN + next_digit) / 10)
			return (1);
	}
	return (0);
}

int	ft_exit_atoi(const char *s, long long *out)
{
	int			i;
	int			neg;
	long long	res;

	i = 0;
	res = 0;
	neg = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		if (s[i++] == '-')
			neg = -1;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		if (check_overflow(res, s[i] - '0', neg))
			return (0);
		res = res * 10 + (s[i] - '0');
		i++;
	}
	*out = res * neg;
	return (1);
}
