/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybazhyna <ybazhyna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 12:28:05 by ybazhyna          #+#    #+#             */
/*   Updated: 2024/07/04 13:40:54 by ybazhyna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*store_remainder(char *data)
{
	char	*remaining;
	int		i;
	int		j;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i])
	{
		free(data);
		return (NULL);
	}
	remaining = (char *)malloc(sizeof(char) * (ft_strlen(data) - i + 1));
	if (!remaining)
		return (NULL);
	i++;
	j = 0;
	while (data[i])
		remaining[j++] = data[i++];
	remaining[j] = '\0';
	free(data);
	return (remaining);
}

static char	*extract_line(char *data)
{
	char	*line;
	int		i;

	i = 0;
	if (!data[i])
		return (NULL);
	while (data[i] && data[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (data[i] && data[i] != '\n')
	{
		line[i] = data[i];
		i++;
	}
	if (data[i] == '\n')
	{
		line[i] = data[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		buffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			if (remainder)
				free(remainder);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remainder = ft_strjoin(remainder, buffer);
		if (ft_strchr(remainder, '\n'))
			break ;
	}
	next_line = extract_line(remainder);
	remainder = store_remainder(remainder);
	return (next_line);
}
