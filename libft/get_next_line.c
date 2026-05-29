/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srichard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 15:21:26 by srichard          #+#    #+#             */
/*   Updated: 2025/12/03 15:11:07 by srichard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*join_and_free(char *stash, char *buffer)
{
	char	*temp;

	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	temp = stash;
	stash = ft_strjoin(temp, buffer);
	free(temp);
	return (stash);
}

static char	*read_and_stash(int fd, char *stash, char *buffer)
{
	ssize_t	b_read;

	b_read = 1;
	while (b_read > 0)
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read == -1)
		{
			free(stash);
			return (NULL);
		}
		if (b_read == 0)
			break ;
		buffer[b_read] = '\0';
		stash = join_and_free(stash, buffer);
		if (!stash || ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*extract_line(char *line_buffer)
{
	char	*stash;
	ssize_t	i;

	i = 0;
	if (!line_buffer || !line_buffer[0])
		return (NULL);
	while (line_buffer[i] != '\0' && line_buffer[i] != '\n')
		i++;
	if (line_buffer[i] == '\0' || line_buffer[i + 1] == '\0')
		return (NULL);
	stash = ft_strdup(line_buffer + i + 1);
	if (!stash)
		return (NULL);
	if (*stash == 0)
	{
		free(stash);
		stash = NULL;
	}
	line_buffer[i + 1] = '\0';
	return (stash);
}

char	*get_next_line(int fd)
{
	char		*line_buffer;
	static char	*stash;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (!stash || !ft_strchr(stash, '\n'))
		line_buffer = read_and_stash(fd, stash, buffer);
	else
		line_buffer = stash;
	free(buffer);
	if (!line_buffer)
	{
		stash = NULL;
		return (NULL);
	}
	stash = extract_line(line_buffer);
	return (line_buffer);
}
