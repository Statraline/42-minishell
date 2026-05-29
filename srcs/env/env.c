/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 13:55:25 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 17:06:25 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new_node->key = key;
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

/* Append a node to t_env linked list */
void	add_env_node(t_env **env_list, t_env *new_node)
{
	t_env	*tmp;

	if (!new_node)
		return ;
	if (!*env_list)
	{
		*env_list = new_node;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

/* Convert envp to linked list */
t_env	*init_env(char **envp)
{
	t_env	*env_list;
	char	*eq_ptr;
	char	*key;
	char	*value;
	int		i;

	env_list = NULL;
	i = -1;
	while (envp && envp[++i])
	{
		eq_ptr = ft_strchr(envp[i], '=');
		if (eq_ptr)
		{
			key = ft_substr(envp[i], 0, eq_ptr - envp[i]);
			value = ft_strdup(eq_ptr + 1);
			if (key && value)
				add_env_node(&env_list, create_env_node(key, value));
			else
			{
				free(key);
				free(value);
			}
		}
	}
	return (env_list);
}
