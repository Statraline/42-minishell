/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 04:55:57 by remusung          #+#    #+#             */
/*   Updated: 2026/05/24 17:06:33 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	cd_error(t_minishell *shell, char *target)
{
	ft_putstr_fd("minishell: cd: ", 2);
	perror(target);
	shell->last_exit_status = 1;
}

int	is_valid_cd_args(char **args)
{
	if (args[1] != NULL && args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (0);
	}
	return (1);
}
