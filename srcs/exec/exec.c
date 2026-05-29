/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 21:14:21 by remusung          #+#    #+#             */
/*   Updated: 2026/05/25 01:58:17 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_child_status(t_minishell *shell, int status)
{
	int	sig;

	if (WIFEXITED(status))
		shell->last_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		shell->last_exit_status = 128 + sig;
		if (sig == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", 2);
		else if (sig == SIGSEGV)
			ft_putstr_fd("Segmentation fault (core dumped)\n", 2);
		else if (sig == SIGINT)
			ft_putchar_fd('\n', 1);
	}
	setup_sig_prompt();
}

void	exec_external_cmd(t_minishell *shell, char **args, t_token *redir_list,
		char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		shell->last_exit_status = 1;
	}
	else if (pid == 0)
	{
		setup_sig_default();
		exec_child(shell, args, redir_list, envp);
	}
	else
	{
		setup_sig_ignore();
		waitpid(pid, &status, 0);
		handle_child_status(shell, status);
	}
}

void	exec(t_minishell *shell, char **args, t_token *redir_list, char **envp)
{
	if (args[0] && is_builtin(args[0]))
	{
		if (shell->in_pipe)
		{
			if (setup_redirections(shell, redir_list) != 0)
				free_all_and_exit(shell, 1);
			exec_builtin(shell, args);
			free_all_and_exit(shell, shell->last_exit_status);
		}
		else
			exec_builtin_redir(shell, args, redir_list);
	}
	else
		exec_external_cmd(shell, args, redir_list, envp);
}
