/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 15:28:50 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 16:58:18 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Create an AST "leaf" (simple command). It starts empty.
Parser fills it with args and redirections as it reads tokens*/
t_ast_node	*create_command_node(void)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_COMMAND;
	node->args = NULL;
	node->redirections = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/* Create an AST "branch" (operator like Pipe, And, Or).
Connects the left and right subtrees*/
t_ast_node	*create_operator_node(t_node_type type, t_ast_node *left,
		t_ast_node *right)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->left = left;
	node->right = right;
	node->args = NULL;
	node->redirections = NULL;
	return (node);
}

/*Check if token is a redirection*/
int	is_redirection(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

/*Check if token is a command delimiter (control operator)*/
int	is_controle_operator(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND
		|| type == TOKEN_OR || type == TOKEN_R_PAREN);
}

/*Create a "subshell"*/
t_ast_node	*create_subshell_node(t_ast_node *child)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->left = child;
	node->right = NULL;
	node->args = NULL;
	node->redirections = NULL;
	return (node);
}
