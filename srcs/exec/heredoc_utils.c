/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:30:00 by remusung          #+#    #+#             */
/*   Updated: 2026/05/13 21:37:29 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	write_heredoc_line(char *line, int fd_out)
{
	ft_putstr_fd(line, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(line);
}

char	*clean_heredoc_delim(char *eol)
{
	char	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(char) * (ft_strlen(eol) + 1));
	if (!clean)
		return (NULL);
	i = 0;
	j = 0;
	while (eol[i])
	{
		if (eol[i] != '\'' && eol[i] != '"')
			clean[j++] = eol[i];
		i++;
	}
	clean[j] = '\0';
	return (clean);
}

char	*heredoc_prompt(void)
{
	char	*line;
	int		stdout_copy;

	stdout_copy = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	line = readline("> ");
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (line);
}

int	handle_parent_heredoc(pid_t pid, int fd[2])
{
	int	status;

	setup_sig_ignore();
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		g_signal = SIGINT;
		return (1);
	}
	return (0);
}
