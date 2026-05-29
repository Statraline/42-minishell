/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 18:48:55 by remusung          #+#    #+#             */
/*   Updated: 2026/05/13 21:38:55 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	handle_expansion_line(char *line, int expand, t_minishell *shell,
		int fd_out)
{
	char	*expanded;

	if (expand)
	{
		expanded = expand_word(line, shell);
		free(line);
		line = expanded;
		if (!line)
			return ;
	}
	ft_putstr_fd(line, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(line);
}

static void	heredoc_child(t_minishell *shell, int fd[2], char *eol, int expand)
{
	char	*line;

	close(fd[0]);
	setup_sig_heredoc();
	while (1)
	{
		line = heredoc_prompt();
		if (!line || g_signal == SIGINT)
			break ;
		if (ft_strcmp(line, eol) == 0)
		{
			free(line);
			break ;
		}
		handle_expansion_line(line, expand, shell, fd[1]);
	}
	close(fd[1]);
	if (g_signal == SIGINT)
		free_all_and_exit(shell, 130);
	free_all_and_exit(shell, 0);
}

static int	fork_heredoc_child(t_minishell *shell, int fd[2], char *eol,
		int expand)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
		heredoc_child(shell, fd, eol, expand);
	return (pid);
}

int	heredoc(t_minishell *shell, t_token *redir_list)
{
	char	*eol;
	char	*clean_eol;
	int		expand;
	int		fd[2];
	pid_t	pid;

	eol = redir_list->next->value;
	clean_eol = clean_heredoc_delim(eol);
	expand = !word_has_quotes(eol);
	if (!clean_eol || pipe(fd) == -1)
		return (free(clean_eol), 1);
	pid = fork_heredoc_child(shell, fd, clean_eol, expand);
	if (pid < 0)
		return (free(clean_eol), 1);
	pid = handle_parent_heredoc(pid, fd);
	free(clean_eol);
	return (pid);
}
