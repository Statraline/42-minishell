/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:30:00 by remusung          #+#    #+#             */
/*   Updated: 2026/05/13 21:37:29 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_string_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	if (tokens == NULL)
		return ;
	while (tokens)
	{
		tmp = tokens->next;
		if (tokens->value)
			free(tokens->value);
		free(tokens);
		tokens = tmp;
	}
}

void	remove_heredoc_tmpfiles(t_minishell *shell)
{
	int	i;

	if (!shell->heredoc_tmpfiles)
		return ;
	i = 0;
	while (shell->heredoc_tmpfiles[i])
	{
		unlink(shell->heredoc_tmpfiles[i]);
		i++;
	}
	free_string_array(shell->heredoc_tmpfiles);
}
