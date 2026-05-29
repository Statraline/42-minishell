/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 07:12:27 by remusung          #+#    #+#             */
/*   Updated: 2026/05/25 03:05:17 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Handle fork error*/
int	fork_error(t_minishell *shell, int fd[2], pid_t launched_pid)
{
	perror("fork");
	close(fd[0]);
	close(fd[1]);
	if (launched_pid > 0)
		waitpid(launched_pid, NULL, 0);
	shell->last_exit_status = 1;
	return (1);
}

void	child_left(t_ast_node *node, t_minishell *shell, int fd[2])
{
	int	status;

	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free_all_and_exit(shell, 1);
	}
	close(fd[0]);
	close(fd[1]);
	shell->in_pipe = 1;
	status = exec_ast(node->left, shell);
	free_all_and_exit(shell, status);
}

void	child_right(t_ast_node *node, t_minishell *shell, int fd[2])
{
	int	status;

	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		free_all_and_exit(shell, 1);
	}
	close(fd[0]);
	close(fd[1]);
	shell->in_pipe = 1;
	status = exec_ast(node->right, shell);
	free_all_and_exit(shell, status);
}

static int	count_env_vars(t_env *env_list)
{
	int		count;
	t_env	*tmp;

	count = 0;
	tmp = env_list;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/* Convert env linked list to char array for execve */
char	**env_list_to_array(t_env *env_list)
{
	int		i;
	char	**array;
	char	*str_tmp;
	t_env	*tmp;

	array = malloc(sizeof(char *) * (count_env_vars(env_list) + 1));
	if (!array)
		return (NULL);
	i = 0;
	tmp = env_list;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
		{
			str_tmp = ft_strjoin(tmp->key, "=");
			array[i] = ft_strjoin(str_tmp, tmp->value);
			free(str_tmp);
			i++;
		}
		tmp = tmp->next;
	}
	array[i] = NULL;
	return (array);
}
