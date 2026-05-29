/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 22:40:17 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/24 17:06:52 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(t_minishell *shell, char **args)
{
	t_env	*tmp;

	if (args[1] != NULL)
	{
		ft_putstr_fd("env: ‘", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd("’: No such file or directory\n", 2);
		shell->last_exit_status = 127;
		return ;
	}
	tmp = shell->env_list;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
		{
			write(STDOUT_FILENO, tmp->key, ft_strlen(tmp->key));
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, tmp->value, ft_strlen(tmp->value));
			write(STDOUT_FILENO, "\n", 1);
		}
		tmp = tmp->next;
	}
}
