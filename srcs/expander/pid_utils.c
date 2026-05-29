/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: remusung <remusung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 22:30:56 by srichard          #+#    #+#             */
/*   Updated: 2026/05/24 16:53:34 by remusung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*Open the file system to extract the actual PID of the actual shell*/
char	*get_shell_pid(void)
{
	int		fd;
	char	buf[256];
	int		ret;
	int		i;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (ft_strdup(""));
	ret = read(fd, buf, 255);
	close(fd);
	if (ret <= 0)
		return (ft_strdup(""));
	buf[ret] = '\0';
	i = 0;
	while (buf[i] && buf[i] != ' ')
		i++;
	buf[i] = '\0';
	return (ft_strdup(buf));
}
