/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:18:44 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 17:05:16 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Rebuild a SINGLE word */
static t_token	*replace_wildcards(t_token *tmp, char **matches, char *exp_str)
{
	t_token	*new_tok;
	int		i;

	(void)exp_str;
	free(tmp->value);
	tmp->value = ft_strdup(matches[0]);
	i = 0;
	while (matches[++i])
	{
		new_tok = create_token(TOKEN_WORD, ft_strdup(matches[i]));
		if (!new_tok)
			break ;
		new_tok->next = tmp->next;
		tmp->next = new_tok;
		tmp = new_tok;
	}
	free_string_array(matches);
	return (tmp);
}

static void	drop_current_token(t_token **current)
{
	t_token	*to_delete;

	to_delete = *current;
	*current = to_delete->next;
	free(to_delete->value);
	free(to_delete);
}

static t_token	*apply_expansion(t_token *tmp, char *exp_str, char *orig)
{
	char	**matches;

	if (ft_strchr(exp_str, '*') && !word_has_quotes(orig))
	{
		matches = get_wildcard_matches(exp_str);
		if (matches)
			tmp = replace_wildcards(tmp, matches, exp_str);
		else
		{
			free(tmp->value);
			tmp->value = ft_strdup(exp_str);
		}
	}
	else
		tmp = split_on_spaces(tmp, exp_str, orig);
	return (tmp);
}

static t_token	**process_word_token(t_token **current, t_minishell *shell)
{
	t_token	*tmp;
	char	*exp_str;

	tmp = *current;
	exp_str = expand_word(tmp->value, shell);
	if (exp_str[0] == '\0' && !word_has_quotes(tmp->value))
	{
		free(exp_str);
		drop_current_token(current);
		return (current);
	}
	tmp = apply_expansion(tmp, exp_str, tmp->value);
	free(exp_str);
	return (&tmp->next);
}

/* Main expander loop, iterates through tokens and updates each WORD value */
void	expander(t_minishell *shell)
{
	t_token	**current;
	t_token	*tmp;

	current = &shell->tokens;
	while (*current)
	{
		tmp = *current;
		if (tmp->type == TOKEN_HEREDOC)
		{
			current = &(*current)->next;
			if (*current && (*current)->type == TOKEN_WORD)
				current = &(*current)->next;
		}
		else if (tmp->type != TOKEN_WORD)
			current = &tmp->next;
		else
			current = process_word_token(current, shell);
	}
}
