/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_collect_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 21:30:00 by remusung          #+#    #+#             */
/*   Updated: 2026/05/23 15:56:50 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_tmpfile_to_list(t_minishell *shell, char *path)
{
	char	**new_array;
	int		count;

	count = 0;
	if (shell->heredoc_tmpfiles)
	{
		while (shell->heredoc_tmpfiles[count])
			count++;
		new_array = malloc(sizeof(char *) * (count + 2));
	}
	else
		new_array = malloc(sizeof(char *) * 2);
	if (!new_array)
		return ;
	count = 0;
	while (shell->heredoc_tmpfiles && shell->heredoc_tmpfiles[count])
	{
		new_array[count] = shell->heredoc_tmpfiles[count];
		count++;
	}
	new_array[count] = path;
	new_array[count + 1] = NULL;
	if (shell->heredoc_tmpfiles)
		free(shell->heredoc_tmpfiles);
	shell->heredoc_tmpfiles = new_array;
}

static int	write_line_to_file(char *line, int fd_out, t_minishell *shell,
		char *eol)
{
	char	*expanded;

	if (!word_has_quotes(eol))
	{
		expanded = expand_word(line, shell);
		free(line);
		line = expanded;
		if (!line)
			return (-1);
	}
	ft_putstr_fd(line, fd_out);
	ft_putchar_fd('\n', fd_out);
	free(line);
	return (0);
}

static char	*get_heredoc_line(void)
{
	char	*line;

	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (NULL);
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		return (line);
	}
	return (readline("> "));
}

static int	write_heredoc_to_file(int fd, t_minishell *shell, t_token *tok)
{
	char	*line;
	char	*eol;
	char	*clean_eol;

	eol = tok->next->value;
	clean_eol = clean_heredoc_delim(eol);
	if (!clean_eol)
		return (close(fd), 1);
	while (1)
	{
		line = get_heredoc_line();
		if (g_signal == SIGINT || !line
			|| ft_strcmp(line, clean_eol) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (write_line_to_file(line, fd, shell, eol) == -1)
			break ;
	}
	free(clean_eol);
	return (close(fd), 0);
}

void	collect_heredocs_from_redir(t_token *redir_list,
		t_minishell *shell)
{
	char	*tmp;
	int		fd;
	int		in_cpy;

	in_cpy = dup(STDIN_FILENO);
	setup_sig_heredoc();
	while (redir_list && g_signal != SIGINT)
	{
		if (redir_list->type == TOKEN_HEREDOC)
		{
			fd = get_unique_heredoc_fd(&tmp);
			if (fd != -1)
			{
				write_heredoc_to_file(fd, shell, redir_list);
				free(redir_list->next->value);
				redir_list->next->value = ft_strdup(tmp);
				redir_list->type = TOKEN_REDIR_IN;
				add_tmpfile_to_list(shell, tmp);
			}
		}
		redir_list = redir_list->next->next;
	}
	dup2(in_cpy, STDIN_FILENO);
	close(in_cpy);
	setup_sig_prompt();
}
