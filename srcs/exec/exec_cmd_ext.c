/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_ext.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 21:14:21 by remusung          #+#    #+#             */
/*   Updated: 2026/05/24 17:06:08 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Search path directories for the executable */
static char	*find_valid_path(char **paths, char *cmd)
{
	char	*part_path;
	char	*full_path;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		part_path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

static char	*handle_empty_path(char *cmd)
{
	char	*valid_path;

	valid_path = ft_strjoin("./", cmd);
	if (!valid_path)
		return (NULL);
	if (access(valid_path, X_OK) == 0)
		return (valid_path);
	free(valid_path);
	return (NULL);
}

static char	*search_in_path_env(char *path_env, char *cmd)
{
	char	**paths;
	char	*valid_path;

	if (path_env[0] == ':' || ft_strnstr(path_env, "::", ft_strlen(path_env)))
	{
		valid_path = handle_empty_path(cmd);
		if (valid_path)
			return (valid_path);
	}
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	valid_path = find_valid_path(paths, cmd);
	free_string_array(paths);
	if (!valid_path && path_env[ft_strlen(path_env) - 1] == ':')
		return (handle_empty_path(cmd));
	return (valid_path);
}

/* Split path variable into an array of paths */
char	*get_cmd_path(t_env *env_list, char *cmd)
{
	char	*path_env;

	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = get_env_value(env_list, "PATH");
	if (!path_env)
		return (NULL);
	if (path_env[0] == '\0')
		return (handle_empty_path(cmd));
	return (search_in_path_env(path_env, cmd));
}

/* Execute external command in child process */
void	exec_child(t_minishell *shell, char **args, t_token *redir_list,
		char **envp)
{
	char	*path;

	if (setup_redirections(shell, redir_list) != 0)
	{
		if (g_signal == SIGINT)
			free_all_and_exit(shell, 130);
		free_all_and_exit(shell, 1);
	}
	check_cmd_edge_cases(shell, args);
	path = get_cmd_path(shell->env_list, args[0]);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_all_and_exit(shell, 127);
	}
	check_is_dir(shell, path);
	execve(path, args, envp);
	handle_exec_error(shell, path, args);
}
