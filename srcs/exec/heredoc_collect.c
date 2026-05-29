/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:30:00 by remusung          #+#    #+#             */
/*   Updated: 2026/05/24 16:47:27 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	collect_heredocs_ast(t_ast_node *node, t_minishell *shell)
{
	if (!node)
		return ;
	if (g_signal == SIGINT)
		return ;
	if ((node->type == NODE_COMMAND || node->type == NODE_SUBSHELL)
		&& node->redirections)
		collect_heredocs_from_redir(node->redirections, shell);
	collect_heredocs_ast(node->left, shell);
	collect_heredocs_ast(node->right, shell);
}

/* Create unique file and return its FD and path */
int	get_unique_heredoc_fd(char **temp_path)
{
	static int	hd_id = 0;
	char		*id_str;
	int			fd;

	while (1)
	{
		id_str = ft_itoa(hd_id++);
		*temp_path = ft_strjoin("/tmp/minishell_heredoc_", id_str);
		free(id_str);
		fd = open(*temp_path, O_CREAT | O_WRONLY
				|O_TRUNC | O_EXCL, 0644);
		if (fd != -1)
			return (fd);
		free(*temp_path);
	}
	return (-1);
}
