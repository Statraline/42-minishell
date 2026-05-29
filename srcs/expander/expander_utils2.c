/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 01:54:37 by remusung          #+#    #+#             */
/*   Updated: 2026/05/22 22:38:49 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_env_var(char *word, int *i, char *new_w, t_minishell *sh)
{
	int		start;
	char	*env_name;

	start = *i;
	while (word[*i] && is_env_char(word[*i]))
		(*i)++;
	env_name = ft_substr(word, start, *i - start);
	new_w = append_str(new_w, get_env_value(sh->env_list, env_name));
	free(env_name);
	(*i)--;
	return (new_w);
}

char	*expand_word(char *word, t_minishell *shell)
{
	char	*new_word;
	int		i;
	int		q;

	new_word = ft_strdup("");
	i = 0;
	q = 0;
	while (word[i])
	{
		if (word[i] == '\'' && q != 2)
			q ^= 1;
		else if (word[i] == '"' && q != 1)
			q ^= 2;
		else if (word[i] == '$' && q != 1)
		{
			if (q == 2 || (word[i + 1] != '\'' && word[i + 1] != '"'))
				new_word = handle_dollar(word, &i, new_word, shell);
		}
		else
			new_word = append_char(new_word, word[i]);
		i++;
	}
	return (new_word);
}

static t_token	*insert_split_words(t_token *tmp, char **words)
{
	t_token	*new_tok;
	int		i;

	free(tmp->value);
	tmp->value = ft_strdup(words[0]);
	i = 0;
	while (words[++i])
	{
		new_tok = create_token(TOKEN_WORD, ft_strdup(words[i]));
		if (!new_tok)
			break ;
		new_tok->next = tmp->next;
		tmp->next = new_tok;
		tmp = new_tok;
	}
	return (tmp);
}

t_token	*split_on_spaces(t_token *tmp, char *expanded, char *orig)
{
	char	**words;

	if (word_has_quotes(orig) || !ft_strchr(expanded, ' '))
	{
		free(tmp->value);
		tmp->value = ft_strdup(expanded);
		return (tmp);
	}
	words = ft_split(expanded, ' ');
	if (!words || !words[0])
	{
		free(tmp->value);
		tmp->value = ft_strdup("");
		if (words)
			free_string_array(words);
		return (tmp);
	}
	tmp = insert_split_words(tmp, words);
	free_string_array(words);
	return (tmp);
}

char	*handle_dollar(char *word, int *i, char *new_word, t_minishell *shell)
{
	char	*tmp_str;

	(*i)++;
	if (word[*i] == '?' || word[*i] == '$')
	{
		if (word[*i] == '?')
			tmp_str = ft_itoa(shell->last_exit_status);
		else
			tmp_str = get_shell_pid();
		new_word = append_str(new_word, tmp_str);
		free(tmp_str);
	}
	else if (ft_isalpha(word[*i]) || word[*i] == '_')
		new_word = extract_env_var(word, i, new_word, shell);
	else if (word[*i] == '*' || word[*i] == '@' || ft_isdigit(word[*i]))
		return (new_word);
	else
	{
		new_word = append_char(new_word, '$');
		(*i)--;
	}
	return (new_word);
}
