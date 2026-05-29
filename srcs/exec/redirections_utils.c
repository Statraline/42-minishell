/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:30:00 by remusung          #+#    #+#             */
/*   Updated: 2026/05/13 21:37:50 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	apply_heredoc_pass(t_minishell *shell, t_token *tmp, int orig_stdin)
{
	if (tmp->type != TOKEN_HEREDOC)
		return (0);
	if (tmp->type == TOKEN_HEREDOC)
	{
		if (dup2(orig_stdin, STDIN_FILENO) == -1)
			return (1);
		return (heredoc(shell, tmp));
	}
	return (0);
}

int	apply_file_pass(t_token *tmp)
{
	if (tmp->type == TOKEN_HEREDOC)
		return (0);
	return (handle_single_redir(tmp, tmp->next->value));
}

int	handle_redir_pass(t_minishell *shell, t_token *redir_list, int orig_stdin,
		int heredoc_only)
{
	t_token	*tmp;

	tmp = redir_list;
	while (tmp != NULL)
	{
		if (!tmp->next || !tmp->next->value)
			return (1);
		if (heredoc_only)
		{
			if (apply_heredoc_pass(shell, tmp, orig_stdin) != 0)
				return (1);
		}
		else if (apply_file_pass(tmp) != 0)
			return (1);
		tmp = tmp->next->next;
	}
	return (0);
}
