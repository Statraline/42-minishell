/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:54:17 by srichard          #+#    #+#             */
/*   Updated: 2026/05/25 02:25:53 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	init_shell(t_minishell *shell, char **envp)
{
	ft_memset(shell, 0, sizeof(t_minishell));
	shell->env_list = init_env(envp);
	shell->last_exit_status = 0;
	shell->ast = NULL;
	shell->is_running = 1;
	shell->heredoc_tmpfiles = NULL;
	setup_sig_prompt();
	setup_terminal_settings();
}

static char	*shell_prompt(void)
{
	char	*line;
	int		stdout_copy;

	if (!isatty(STDIN_FILENO))
	{
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (NULL);
		if (ft_strlen(line) > 0 && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		return (line);
	}
	stdout_copy = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	line = readline(PROMPT);
	dup2(stdout_copy, STDOUT_FILENO);
	close(stdout_copy);
	return (line);
}

static void	process_line(t_minishell *shell, char *line)
{
	t_token	*tokens_ptr;

	add_history(line);
	shell->tokens = lexer(line, shell);
	if (shell->tokens)
	{
		expander(shell);
		if (shell->tokens)
		{
			tokens_ptr = shell->tokens;
			shell->ast = parse_logical(&tokens_ptr);
			if (shell->ast)
				process_ast(shell);
			else
				shell->last_exit_status = 2;
		}
		free_tokens(shell->tokens);
		shell->tokens = NULL;
	}
}

static int	check_events(t_minishell *shell, char *line)
{
	if (!line)
	{
		if (isatty(STDIN_FILENO))
			printf("exit\n");
		return (0);
	}
	if (g_signal == SIGINT)
	{
		shell->last_exit_status = 130;
		g_signal = 0;
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_minishell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	while (shell.is_running)
	{
		line = shell_prompt();
		if (!check_events(&shell, line))
			break ;
		if (*line)
		{
			process_line(&shell, line);
			setup_terminal_settings();
		}
		free(line);
	}
	free_all_and_exit(&shell, shell.last_exit_status);
	return (0);
}
