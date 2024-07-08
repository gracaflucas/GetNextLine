/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 20:40:19 by lufiguei          #+#    #+#             */
/*   Updated: 2024/07/08 19:10:17 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*readfile(int fd, char *buffer, char *stash);
static char	*get_line(char *line);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (fd == -1 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	if (buffer == NULL)
		return (NULL);
	line = readfile(fd, buffer, stash);
	free(buffer);
	if (line == NULL)
		return (NULL);
	stash = get_line(line);
	return (line);
}

static char	*readfile(int fd, char *buffer, char *stash)
{
	char	*tmp;
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(stash);
			return (NULL);
		}
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (stash == NULL)
			stash = ft_strdup("");
		tmp = stash;
		stash = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (stash);
}

static char	*get_line(char *line)
{
	ssize_t	i;
	char	*new_stash;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0' || line[1] == '\0')
		return (NULL);
	new_stash = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*new_stash == '\0')
	{
		free(new_stash);
		new_stash = NULL;
	}
	line[i + 1] = '\0';
	return (new_stash);
}
