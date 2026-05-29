/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 02:06:05 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/25 03:07:11 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

/*Bubble sort for a array of pointor */
void	sort_env(t_env **tab, int size)
{
	int		i;
	int		j;
	t_env	*tmp;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(tab[j]->key, tab[j + 1]->key) > 0)
			{
				tmp = tab[j];
				tab[j] = tab[j + 1];
				tab[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Display vars in Bash format (declare -x) */
void	display_and_free_tab(t_env **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		printf("declare -x %s", tab[i]->key);
		if (tab[i]->value)
			printf("=\"%s\"", tab[i]->value);
		printf("\n");
		i++;
	}
	free(tab);
}

/*Create a copy of the var, sort it and display*/
void	print_sorted_env(t_minishell *shell)
{
	t_env	**tab;
	t_env	*tmp;
	int		i;
	int		count;

	count = 0;
	tmp = shell->env_list;
	while (tmp && ++count)
		tmp = tmp->next;
	tab = malloc(sizeof(t_env *) * count);
	if (!tab)
		return ;
	i = 0;
	tmp = shell->env_list;
	while (tmp)
	{
		tab[i++] = tmp;
		tmp = tmp->next;
	}
	sort_env(tab, count);
	display_and_free_tab(tab, count);
}
