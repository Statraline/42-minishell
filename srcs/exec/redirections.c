/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 21:15:47 by remusung          #+#    #+#             */
/*   Updated: 2026/05/13 21:38:00 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	open_error(char *file)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	if (errno == ENOENT)
		ft_putstr_fd(": No such file or directory\n", 2);
	else if (errno == EACCES)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (errno == EISDIR)
		ft_putstr_fd(": Is a directory\n", 2);
	else
		ft_putstr_fd(": Error\n", 2);
	return (1);
}

int	handle_single_redir(t_token *tmp, char *file)
{
	int	fd;

	fd = -1;
	if (tmp->type == TOKEN_REDIR_IN)
		fd = open(file, O_RDONLY);
	else if (tmp->type == TOKEN_REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (tmp->type == TOKEN_APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		return (0);
	if (fd == -1)
		return (open_error(file));
	if (tmp->type == TOKEN_REDIR_IN)
	{
		if (dup2(fd, STDIN_FILENO) == -1)
			return (close(fd), 1);
	}
	else if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), 1);
	close(fd);
	return (0);
}

int	apply_redir_logic(t_minishell *shell, t_token *tmp, int orig_stdin)
{
	if (tmp->type == TOKEN_HEREDOC)
	{
		if (dup2(orig_stdin, STDIN_FILENO) == -1)
			return (1);
		return (heredoc(shell, tmp));
	}
	else
		return (handle_single_redir(tmp, tmp->next->value));
}

int	setup_redirections(t_minishell *shell, t_token *redir_list)
{
	int	orig_stdin;

	orig_stdin = dup(STDIN_FILENO);
	if (orig_stdin == -1)
		return (1);
	if (handle_redir_pass(shell, redir_list, orig_stdin, 1) != 0
		|| handle_redir_pass(shell, redir_list, orig_stdin, 0) != 0)
	{
		close(orig_stdin);
		return (1);
	}
	close(orig_stdin);
	return (0);
}
