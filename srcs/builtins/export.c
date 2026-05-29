/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/03 15:22:13 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/24 17:07:42 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	update_existing_env(t_env *node, char *key, char *value, int append)
{
	char	*new_val;

	free(key);
	if (!value)
		return ;
	if (append && node->value)
	{
		new_val = ft_strjoin(node->value, value);
		free(node->value);
		free(value);
		node->value = new_val;
	}
	else
	{
		if (node->value)
			free(node->value);
		node->value = value;
	}
}

void	update_or_create_env(t_minishell *shell, char *key, char *value
		, int append)
{
	t_env	*node;

	node = find_env_var(shell->env_list, key);
	if (node != NULL)
		update_existing_env(node, key, value, append);
	else
	{
		node = create_env_node(key, value);
		if (node)
			add_env_node(&(shell->env_list), node);
	}
}

static void	process_export_arg(t_minishell *shell, char *arg)
{
	char	*key;
	char	*value;
	char	*eq_ptr;
	int		append;

	append = 0;
	eq_ptr = ft_strchr(arg, '=');
	if (eq_ptr && eq_ptr > arg && *(eq_ptr - 1) == '+')
		append = 1;
	key = extract_key(arg);
	if (!is_valid_env_key(key))
	{
		print_export_error(arg);
		free(key);
		shell->last_exit_status = 1;
	}
	else
	{
		value = extract_value(arg);
		update_or_create_env(shell, key, value, append);
	}
}

void	ft_export(t_minishell *shell, char **args)
{
	int		i;

	shell->last_exit_status = 0;
	if (!args[1])
		return (print_sorted_env(shell));
	i = 1;
	while (args[i])
	{
		process_export_arg(shell, args[i]);
		i++;
	}
}
