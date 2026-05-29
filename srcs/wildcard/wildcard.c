/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <srichard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 17:24:45 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 20:37:37 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	match_pattern(char *pattern, char *word)
{
	if (*pattern == '\0' && *word == '\0')
		return (1);
	if (*pattern == '*' && *(pattern + 1) != '\0' && *word == '\0')
		return (0);
	if (*pattern == '*')
		return (match_pattern(pattern + 1, word) || match_pattern (pattern,
				word + 1));
	if (*pattern == *word)
		return (match_pattern(pattern + 1, word + 1));
	return (0);
}

static int	count_matches(char *pattern)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(".");
	if (!dir)
		return (0);
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_name[0] != '.' || pattern[0] == '.')
		{
			if (match_pattern(pattern, entry->d_name))
				count++;
		}
		entry = (void *)readdir(dir);
	}
	closedir(dir);
	return (count);
}

static void	sort_matches(char **matches, int count)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (strcasecmp_custom(matches[i], matches[j]) > 0)
			{
				tmp = matches[i];
				matches[i] = matches[j];
				matches[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	populate_matches(DIR *dir, char **matches, char *pattern)
{
	struct dirent	*entry;
	int				i;

	i = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if ((entry->d_name[0] != '.' || pattern[0] == '.')
			&& match_pattern(pattern, entry->d_name))
			matches[i++] = ft_strdup(entry->d_name);
		entry = readdir(dir);
	}
	matches[i] = NULL;
	sort_matches(matches, i);
}

char	**get_wildcard_matches(char *pattern)
{
	DIR				*dir;
	char			**matches;
	int				count;

	count = count_matches(pattern);
	if (count == 0)
		return (NULL);
	matches = malloc(sizeof(char *) * (count + 1));
	if (!matches)
		return (NULL);
	dir = opendir(".");
	if (!dir)
		return (free(matches), NULL);
	populate_matches(dir, matches, pattern);
	closedir(dir);
	return (matches);
}
