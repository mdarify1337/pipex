/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarify <mdarify@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 10:07:34 by mdarify           #+#    #+#             */
/*   Updated: 2023/01/06 15:09:33 by mdarify          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*filed_read(int fd, char *buffer)
{
	char	*line;
	int		m;

	m = 1;
	line = malloc((BUFFER_SIZE + 1) * sizeof(char));
	while (!strchr_newline(buffer) && m)
	{
		m = read(fd, line, BUFFER_SIZE);
		if (m == -1)
		{
			free(line);
			if (!buffer)
				return (NULL);
			return (buffer);
		}
		line[m] = 0;
		buffer = ft_strjoin(buffer, line);
	}
	free(line);
	return (buffer);
}

char	*new_line(char *buffer)
{
	char	*line;
	int		m;

	m = 0;
	if (!buffer[0])
		return (NULL);
	while (buffer[m] != '\n' && buffer[m])
		m++;
	m = m + 1;
	line = ft_substr(buffer, 0, m);
	return (line);
}

char	*next_line(char *buffer)
{
	char	*line;
	int		m;

	m = 0;
	while (buffer[m])
	{
		if (buffer[m] == '\n')
		{
			line = ft_substr(buffer, m + 1, ft_strlen(buffer) - m + 1);
			free(buffer);
			return (line);
		}
		m++;
	}
	free(buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;
	int			i;

	i = 0;
	if (fd < 0 || BUFFER_SIZE == 0)
		return (NULL);
	buffer[fd] = filed_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = new_line(buffer[fd]);
	buffer[fd] = next_line(buffer[fd]);
	return (line);
}
