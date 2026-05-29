/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 17:20:16 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 18:44:43 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_ast(t_ast_node *node)
{
	if (!node)
		return ;
	free_ast(node->left);
	free_ast(node->right);
	if (node->type == NODE_COMMAND)
	{
		if (node->args)
			free_string_array(node->args);
		if (node->redirections)
			free_tokens(node->redirections);
	}
	free(node);
}

void	free_env(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list->next;
		if (env_list->key)
			free(env_list->key);
		if (env_list->value)
			free(env_list->value);
		free(env_list);
		env_list = tmp;
	}
}

void	free_all_and_exit(t_minishell *shell, int status)
{
	if (shell->tokens)
		free_tokens(shell->tokens);
	if (shell->ast)
		free_ast(shell->ast);
	if (shell->env_list)
		free_env(shell->env_list);
	if (shell->env_array)
		free_string_array(shell->env_array);
	remove_heredoc_tmpfiles(shell);
	rl_clear_history();
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(status);
}
