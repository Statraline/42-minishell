/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 00:35:35 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/24 16:40:23 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_pwd(t_minishell *shell, char **args)
{
	char	buf[PATH_MAX];
	char	*pwd_env;

	(void)args;
	pwd_env = get_env_value(shell->env_list, "PWD");
	if (pwd_env && pwd_env[0] != '\0')
	{
		ft_putstr_fd(pwd_env, 1);
		write(1, "\n", 1);
		shell->last_exit_status = 0;
	}
	else if (getcwd(buf, sizeof(buf)) != NULL)
	{
		ft_putstr_fd(buf, 1);
		write(1, "\n", 1);
		shell->last_exit_status = 0;
	}
	else
	{
		perror("minishell: pwd");
		shell->last_exit_status = 1;
	}
}
