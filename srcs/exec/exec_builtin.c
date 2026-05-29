/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 21:09:44 by remusung          #+#    #+#             */
/*   Updated: 2026/05/25 02:31:46 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"pwd") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	exec_builtin(t_minishell *shell, char **args)
{
	shell->last_exit_status = 0;
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(shell, args), shell->last_exit_status);
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(shell, args), shell->last_exit_status);
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(shell, args), shell->last_exit_status);
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(shell, args), shell->last_exit_status);
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(shell, args), shell->last_exit_status);
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(shell, args), shell->last_exit_status);
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(shell, args), shell->last_exit_status);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		shell->last_exit_status = 127;
	}
	return (shell->last_exit_status);
}

static void	exec_without_redir(int saved_stdin, int saved_stdout,
	t_minishell *shell, char **args)
{
	shell->last_exit_status = exec_builtin(shell, args);
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}

void	exec_builtin_redir(t_minishell *shell, char **args, t_token *redir_list)
{
	int	saved_stdin;
	int	saved_stdout;
	int	redir_status;

	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	redir_status = setup_redirections(shell, redir_list);
	if (redir_status != 0)
	{
		dup2(saved_stdin, STDIN_FILENO);
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdin);
		close(saved_stdout);
		if (g_signal == SIGINT)
			shell->last_exit_status = 130;
		else
			shell->last_exit_status = 1;
		return ;
	}
	exec_without_redir(saved_stdin, saved_stdout, shell, args);
}
