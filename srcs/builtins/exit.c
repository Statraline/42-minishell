/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 04:19:01 by reginamwika       #+#    #+#             */
/*   Updated: 2026/05/24 17:07:06 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	parse_exit_arg(const char *s, long long *out)
{
	if (!ft_exit_atoi(s, out))
		return (0);
	return (1);
}

static void	print_exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	handle_exit_arg(t_minishell *shell, char **args)
{
	long long	val;

	if (!is_num(args[1]))
	{
		print_exit_error(args[1]);
		shell->last_exit_status = 2;
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		shell->last_exit_status = 2;
		return ;
	}
	else if (!parse_exit_arg(args[1], &val))
	{
		print_exit_error(args[1]);
		shell->last_exit_status = 2;
	}
	else
		shell->last_exit_status = (unsigned char)(val & 0xFF);
	shell->is_running = 0;
}

void	ft_exit(t_minishell *shell, char **args)
{
	ft_putstr_fd("exit\n", 2);
	if (!args[1])
	{
		shell->is_running = 0;
		return ;
	}
	handle_exit_arg(shell, args);
}
