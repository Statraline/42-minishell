/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:47:34 by srichard          #+#    #+#             */
/*   Updated: 2026/04/23 16:14:15 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r');
}

int	is_operator(char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '|' || *str == '<' || *str == '>')
		return (1);
	if (*str == '&' || *str == '(' || *str == ')')
		return (1);
	return (0);
}

int	get_word_len(char *str)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
			in_quote = str[i];
		else if (in_quote && str[i] == in_quote)
			in_quote = 0;
		else if (!in_quote && (is_space(str[i]) || is_operator(str + i)))
			break ;
		i++;
	}
	return (i);
}

int	check_unclosed_quotes(char *input)
{
	int		i;
	char	in_quote;

	i = 0;
	in_quote = 0;
	while (input[i])
	{
		if (!in_quote && (input[i] == '\'' || input[i] == '"'))
			in_quote = input[i];
		else if (in_quote && input[i] == in_quote)
			in_quote = 0;
		i++;
	}
	if (in_quote != 0)
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char) s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
