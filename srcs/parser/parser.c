/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 16:02:32 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 17:00:15 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Count arguments of a simple command*/
int	count_args(t_token *tokens)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = tokens;
	while (tmp && !is_controle_operator(tmp->type))
	{
		if (is_redirection(tmp->type))
		{
			if (tmp->next && tmp->next->type == TOKEN_WORD)
				tmp = tmp->next->next;
			else
				tmp = tmp->next;
		}
		else if (tmp->type == TOKEN_WORD)
		{
			count++;
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
	return (count);
}

/*Extract redirection, check syntax, and advance pointer*/
int	handle_redirection(t_ast_node *node, t_token **tokens)
{
	t_token	*redir_op;
	t_token	*target_file;

	redir_op = *tokens;
	if (!redir_op->next || redir_op->next->type != TOKEN_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (redir_op->next)
		{
			ft_putstr_fd(redir_op->next->value, 2);
			ft_putstr_fd("'\n", 2);
		}
		else
			ft_putstr_fd("newline'\n", 2);
		return (0);
	}
	target_file = redir_op->next;
	add_token(&(node->redirections), create_token(redir_op->type,
			ft_strdup(redir_op->value)));
	add_token(&(node->redirections), create_token(target_file->type,
			ft_strdup(target_file->value)));
	*tokens = target_file->next;
	return (1);
}

t_ast_node	*parse_pipeline(t_token **tokens)
{
	t_ast_node	*left_node;
	t_ast_node	*right_node;

	left_node = parse_primary(tokens);
	if (!left_node)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || is_controle_operator((*tokens)->type))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|' \n",
				2);
			free_ast(left_node);
			return (NULL);
		}
		right_node = parse_primary(tokens);
		if (!right_node)
		{
			free_ast(left_node);
			return (NULL);
		}
		left_node = create_operator_node(NODE_PIPE, left_node, right_node);
	}
	return (left_node);
}

static t_ast_node	*get_logical_right(t_token **tokens, t_ast_node *left)
{
	t_ast_node	*right;

	if (!*tokens || is_controle_operator((*tokens)->type))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
		free(left);
		return (NULL);
	}
	right = parse_pipeline(tokens);
	if (!right)
		free_ast(left);
	return (right);
}

/*Handle && and || logical operators (lowest priority)*/
t_ast_node	*parse_logical(t_token **tokens)
{
	t_ast_node		*left;
	t_ast_node		*right;
	t_token_type	op;

	if (!*tokens)
		return (NULL);
	if ((*tokens)->type == TOKEN_AND || (*tokens)->type == TOKEN_OR
		|| (*tokens)->type == TOKEN_PIPE)
		return (syntax_error_node(*tokens));
	left = parse_pipeline(tokens);
	while (left && *tokens && ((*tokens)->type == TOKEN_AND
			|| (*tokens)->type == TOKEN_OR))
	{
		op = (*tokens)->type;
		*tokens = (*tokens)->next;
		right = get_logical_right(tokens, left);
		if (!right)
			return (NULL);
		if (op == TOKEN_AND)
			left = create_operator_node(NODE_AND, left, right);
		else
			left = create_operator_node(NODE_OR, left, right);
	}
	return (left);
}
