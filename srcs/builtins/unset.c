/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 20:19:27 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/25 03:06:58 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

/*Iterate through the list to unset and relink the next node*/
void	unset_next_node(t_env *tmp, char *arg)
{
	t_env	*to_unset;

	while (tmp != NULL && tmp->next != NULL)
	{
		if (ft_strcmp(tmp->next->key, arg) == 0)
		{
			to_unset = tmp->next;
			tmp->next = to_unset->next;
			free_env_node(to_unset);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_unset(t_minishell *shell, char **args)
{
	t_env	*to_unset;
	int		i;

	i = 1;
	shell->last_exit_status = 0;
	while (args[i])
	{
		if (shell->env_list && ft_strcmp((shell->env_list)->key, args[i]) == 0)
		{
			to_unset = shell->env_list;
			shell->env_list = shell->env_list->next;
			free_env_node(to_unset);
		}
		else
			unset_next_node(shell->env_list, args[i]);
		i++;
	}
}
