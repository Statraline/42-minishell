/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:39:59 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/24 17:06:50 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_env_key(char *key)
{
	if (!key || !*key)
		return (0);
	if (ft_isdigit(key[0]))
		return (0);
	while (*key)
	{
		if (!(ft_isalnum(*key) || *key == '_'))
			return (0);
		key++;
	}
	return (1);
}

char	*extract_key(char *arg)
{
	char	*eq_ptr;
	char	*key;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr)
	{
		if (eq_ptr > arg && *(eq_ptr - 1) == '+')
			key = ft_substr(arg, 0, eq_ptr - arg - 1);
		else
			key = ft_substr(arg, 0, eq_ptr - arg);
		return (key);
	}
	return (ft_strdup(arg));
}

char	*extract_value(char *arg)
{
	char	*eq_ptr;
	char	*value;

	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr)
	{
		value = ft_strdup(eq_ptr + 1);
		return (value);
	}
	return (NULL);
}

t_env	*find_env_var(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
