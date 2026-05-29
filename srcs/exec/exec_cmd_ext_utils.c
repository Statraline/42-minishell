/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/01 15:26:47 by srichard          #+#    #+#             */
/*   Updated: 2026/05/12 18:06:50 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_cmd_edge_cases(t_minishell *shell, char **args)
{
	if (!args[0])
		free_all_and_exit(shell, 0);
	if (ft_strcmp(args[0], ".") == 0)
	{
		ft_putstr_fd("minishell: .: filename argument required\n", 2);
		free_all_and_exit(shell, 2);
	}
	if (ft_strcmp(args[0], "..") == 0)
	{
		ft_putstr_fd("minishell: ..: command not found\n", 2);
		free_all_and_exit(shell, 127);
	}
	if (args[0][0] == '\0')
	{
		ft_putstr_fd("minishell: '': command not found\n", 2);
		free_all_and_exit(shell, 127);
	}
}

void	check_is_dir(t_minishell *shell, char *path)
{
	struct stat	st;

	if (stat(path, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(path);
		free_all_and_exit(shell, 126);
	}
}

void	handle_exec_error(t_minishell *shell, char *path, char **args)
{
	ft_putstr_fd("minishell: ", 2);
	if (errno == EACCES)
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(path);
		free_all_and_exit(shell, 126);
	}
	else if (errno == ENOENT && ft_strchr(path, '/'))
	{
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(path);
		free_all_and_exit(shell, 127);
	}
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	free_all_and_exit(shell, 127);
}
