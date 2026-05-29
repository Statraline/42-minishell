/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 18:33:39 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 16:54:29 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Allocate and initialize new node */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

/* Append node to existing list */
void	add_token(t_token **tokens, t_token *new_token)
{
	t_token	*tmp;

	if (!new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_token;
}

int	check_syntax_subshell(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		if (tmp->type == TOKEN_R_PAREN && tmp->next)
		{
			if (tmp->next->type == TOKEN_WORD
				|| tmp->next->type == TOKEN_L_PAREN)
			{
				ft_putstr_fd("minishell:"
					"syntax error near unexpected token\n", 2);
				return (1);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}
