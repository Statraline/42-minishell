/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 03:01:19 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/24 17:06:41 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Update PWD and OLDPWD in env list */
static void	update_pwd_oldpwd(t_minishell *shell, char *old_pwd)
{
	char	buf[PATH_MAX];
	char	*new_pwd;

	update_or_create_env(shell, ft_strdup("OLDPWD"), ft_strdup(old_pwd), 0);
	if (getcwd(buf, sizeof(buf)))
	{
		new_pwd = ft_strdup(buf);
		update_or_create_env(shell, ft_strdup("PWD"), new_pwd, 0);
	}
}

static char	*get_env_or_error(t_minishell *shell, char *var, char *msg)
{
	char	*val;

	val = get_env_value(shell->env_list, var);
	if (!val || val[0] == '\0')
	{
		ft_putstr_fd(msg, 2);
		return (NULL);
	}
	return (val);
}

static char	*get_cd_target(t_minishell *shell, char **args)
{
	if (!is_valid_cd_args(args))
		return (NULL);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
		return (get_env_or_error(shell, "HOME",
				"minishell: cd: HOME not set\n"));
	if (ft_strcmp(args[1], "-") == 0)
		return (get_env_or_error(shell, "OLDPWD",
				"minishell: cd: OLDPWD not set\n"));
	if (args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (NULL);
	}
	return (args[1]);
}

void	ft_cd(t_minishell *shell, char **args)
{
	char	*target;
	char	old_pwd[PATH_MAX];

	if (args[1] && args[1][0] == '\0')
		return ((void)(shell->last_exit_status = 0));
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		old_pwd[0] = '\0';
	target = get_cd_target(shell, args);
	if (!target)
		return ((void)(shell->last_exit_status = 1));
	if (chdir(target) != 0)
		cd_error(shell, target);
	else
	{
		if (args[1] != NULL && ft_strcmp(args[1], "-") == 0)
		{
			ft_putstr_fd(target, 1);
			ft_putchar_fd('\n', 1);
		}
		if (old_pwd[0] != '\0')
			update_pwd_oldpwd(shell, old_pwd);
		shell->last_exit_status = 0;
	}
}
