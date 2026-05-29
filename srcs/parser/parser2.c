/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/07 16:57:28 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 17:01:00 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	process_cmd_token(t_ast_node *node, t_token **tok, int *i)
{
	if (is_redirection((*tok)->type))
	{
		if (!handle_redirection(node, tok))
			return (0);
	}
	else if ((*tok)->type == TOKEN_WORD)
	{
		node->args[*i] = ft_strdup((*tok)->value);
		(*i)++;
		*tok = (*tok)->next;
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd((*tok)->value, 2);
		ft_putstr_fd("'\n", 2);
		*tok = (*tok)->next;
		return (0);
	}
	return (1);
}

t_ast_node	*parse_command(t_token **tokens)
{
	t_ast_node	*node;
	int			i;
	int			nb_args;

	node = create_command_node();
	if (!node)
		return (NULL);
	nb_args = count_args(*tokens);
	node->args = ft_calloc(nb_args + 1, sizeof(char *));
	if (!node->args)
	{
		free_ast(node);
		return (NULL);
	}
	i = 0;
	while (*tokens && !is_controle_operator((*tokens)->type))
	{
		if (!process_cmd_token(node, tokens, &i))
		{
			free_ast(node);
			return (NULL);
		}
	}
	node->args[i] = NULL;
	return (node);
}

static t_ast_node	*parse_subshell(t_token **tokens)
{
	t_ast_node	*n;
	t_ast_node	*sub;

	*tokens = (*tokens)->next;
	n = parse_logical(tokens);
	if (!n)
		return (NULL);
	if (!*tokens || (*tokens)->type != TOKEN_R_PAREN)
	{
		ft_putstr_fd("minishell: syntax error: unclosed parenthesis\n", 2);
		free_ast(n);
		return (NULL);
	}
	*tokens = (*tokens)->next;
	sub = create_subshell_node(n);
	while (sub && *tokens && is_redirection((*tokens)->type))
	{
		if (!handle_redirection(sub, tokens))
		{
			free_ast(sub);
			return (NULL);
		}
	}
	return (sub);
}

/* Determine if token is a parenthesis or a standard simple command */
t_ast_node	*parse_primary(t_token **tokens)
{
	if (!*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_L_PAREN)
		return (parse_subshell(tokens));
	return (parse_command(tokens));
}

t_ast_node	*syntax_error_node(t_token *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token->value, 2);
	ft_putstr_fd("'\n", 2);
	return (NULL);
}
