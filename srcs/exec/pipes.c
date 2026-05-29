/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 01:38:59 by remusung          #+#    #+#             */
/*   Updated: 2026/05/24 16:48:53 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Wait for child processes to finish */
static void	wait_pipes(t_minishell *shell, pid_t pid[2])
{
	int	status;

	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	handle_child_status(shell, status);
}

static void	exec_subshell(t_ast_node *node, t_minishell *shell)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (setup_redirections(shell, node->redirections) != 0)
			free_all_and_exit(shell, 1);
		status = exec_ast(node->left, shell);
		free_all_and_exit(shell, status);
	}
	waitpid(pid, &status, 0);
	handle_child_status(shell, status);
}

/* Handle &&, ||, and parentheses */
static void	exec_logical_and_subshell(t_ast_node *node, t_minishell *shell)
{
	if (node->type == NODE_AND || node->type == NODE_OR)
	{
		exec_ast(node->left, shell);
		if ((node->type == NODE_AND && shell->last_exit_status == 0)
			|| (node->type == NODE_OR && shell->last_exit_status != 0))
			exec_ast(node->right, shell);
	}
	else if (node->type == NODE_SUBSHELL)
		exec_subshell(node, shell);
}

/* Recursively traverse AST and execute commands */
int	exec_ast(t_ast_node *node, t_minishell *shell)
{
	if (!node)
		return (shell->last_exit_status);
	if (node->type == NODE_PIPE)
		exec_pipe(node, shell);
	else if (node->type == NODE_COMMAND)
	{
		shell->env_array = env_list_to_array(shell->env_list);
		exec(shell, node->args, node->redirections, shell->env_array);
		free_string_array(shell->env_array);
		shell->env_array = NULL;
	}
	else if (node->type == NODE_AND || node->type == NODE_OR
		|| node->type == NODE_SUBSHELL)
		exec_logical_and_subshell(node, shell);
	return (shell->last_exit_status);
}

/* Execute piped command */
void	exec_pipe(t_ast_node *node, t_minishell *shell)
{
	int		fd[2];
	pid_t	pid[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), (void)(shell->last_exit_status = 1));
	pid[0] = fork();
	if (pid[0] < 0)
		return ((void)fork_error(shell, fd, -1));
	if (pid[0] == 0)
		child_left(node, shell, fd);
	pid[1] = fork();
	if (pid[1] < 0)
		return ((void)fork_error(shell, fd, pid[0]));
	if (pid[1] == 0)
		child_right(node, shell, fd);
	close(fd[0]);
	close(fd[1]);
	setup_sig_ignore();
	wait_pipes(shell, pid);
}
