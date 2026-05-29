/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 14:18:39 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 17:04:47 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return ("");
}

/*Add a char at the end a the str*/
char	*append_char(char *str, char c)
{
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = malloc(sizeof(char) * (len + 2));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = c;
	new_str[i + 1] = '\0';
	if (str)
		free(str);
	return (new_str);
}

/* Copy and Append a nwe str at the end */
char	*append_str(char *s1, char *s2)
{
	char	*new_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	new_str = ft_strjoin(s1, s2);
	free(s1);
	return (new_str);
}

/* Check if character is valid for variable name */
int	is_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/* Check if word contains quotes */
int	word_has_quotes(char *word)
{
	return (ft_strchr(word, '\'') != NULL || ft_strchr(word, '"') != NULL);
}
