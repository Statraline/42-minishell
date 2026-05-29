/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/23 15:49:05 by srichard          #+#    #+#             */
/*   Updated: 2026/05/23 15:53:26 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_ast(t_minishell *shell)
{
	collect_heredocs_ast(shell->ast, shell);
	if (g_signal == SIGINT)
	{
		shell->last_exit_status = 130;
		g_signal = 0;
	}
	else
		exec_ast(shell->ast, shell);
	free_ast(shell->ast);
	shell->ast = NULL;
}
