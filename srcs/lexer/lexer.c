/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 17:42:49 by srichard          #+#    #+#             */
/*   Updated: 2026/05/12 16:56:48 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_token	*handle_lexer_errors(t_token *token, t_minishell *shell)
{
	if (check_syntax_subshell(token))
	{
		free_tokens(token);
		shell->last_exit_status = 2;
		return (NULL);
	}
	return (token);
}

t_token	*lexer(char *input, t_minishell *shell)
{
	t_token	*token;
	int		i;

	if (check_unclosed_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (NULL);
	}
	token = NULL;
	i = 0;
	while (input[i])
	{
		while (input[i] == ' ' || input[i] == '\t')
			i++;
		if (input[i] == '\n')
			ft_putstr_fd("minishell: warning: multi-line ignored\n", 2);
		if (!input[i] || input[i] == '\n')
			break ;
		if (is_operator(input + i))
			add_token(&token, extract_operator(input, &i));
		else
			add_token(&token, extract_word(input, &i));
	}
	return (handle_lexer_errors(token, shell));
}

t_token	*extract_word(char *input, int *i)
{
	int		len;
	char	*word_str;
	t_token	*new_token;

	len = get_word_len(input + *i);
	word_str = ft_substr(input, *i, len);
	if (!word_str)
		return (NULL);
	new_token = create_token(TOKEN_WORD, word_str);
	*i += len;
	return (new_token);
}

static t_token_type	get_op_type(char *s, int *len)
{
	*len = 2;
	if (s[0] == '<' && s[1] == '<')
		return (TOKEN_HEREDOC);
	if (s[0] == '>' && s[1] == '>')
		return (TOKEN_APPEND);
	if (s[0] == '&' && s[1] == '&')
		return (TOKEN_AND);
	if (s[0] == '|' && s[1] == '|')
		return (TOKEN_OR);
	*len = 1;
	if (s[0] == '|')
		return (TOKEN_PIPE);
	if (s[0] == '<')
		return (TOKEN_REDIR_IN);
	if (s[0] == '>')
		return (TOKEN_REDIR_OUT);
	if (s[0] == '(')
		return (TOKEN_L_PAREN);
	if (s[0] == ')')
		return (TOKEN_R_PAREN);
	return (TOKEN_WORD);
}

t_token	*extract_operator(char *input, int *i)
{
	t_token_type	type;
	char			*op_str;
	int				len;

	type = get_op_type(input + *i, &len);
	op_str = ft_substr(input, *i, len);
	if (!op_str)
		return (NULL);
	*i += len;
	return (create_token(type, op_str));
}
