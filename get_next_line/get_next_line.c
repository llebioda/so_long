/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llebioda <llebioda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:47:57 by llebioda          #+#    #+#             */
/*   Updated: 2024/11/19 14:04:15 by llebioda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *r);
char	*join_buffer(char *buf1, char *buf2);
char	*get_line(char *buffer);
char	*remove_line(char *buffer);

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (buffer == NULL || !ft_strchr(buffer, '\n'))
	{
		buffer = read_file(fd, buffer);
		if (buffer == NULL)
			return (NULL);
	}
	line = get_line(buffer);
	temp = remove_line(buffer);
	free(buffer);
	buffer = temp;
	return (line);
}

char	*read_file(int fd, char *buffer)
{
	char	*read_buf;
	int		len;

	read_buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (read_buf == NULL)
		return (NULL);
	len = read(fd, read_buf, BUFFER_SIZE);
	while (len > 0)
	{
		read_buf[len] = '\0';
		buffer = join_buffer(buffer, read_buf);
		if (ft_strchr(read_buf, '\n'))
			break ;
		len = read(fd, read_buf, BUFFER_SIZE);
	}
	free(read_buf);
	return (buffer);
}

char	*join_buffer(char *buf1, char *buf2)
{
	char	*buf;

	buf = ft_strjoin(buf1, buf2);
	free(buf1);
	return (buf);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (line == NULL)
		return (NULL);
	if (buffer[i] == '\n')
		line[i--] = '\n';
	while (i >= 0)
	{
		line[i] = buffer[i];
		i--;
	}
	return (line);
}

char	*remove_line(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	if (buffer == NULL || buffer[0] == '\0')
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new_buffer = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (new_buffer == NULL)
		return (NULL);
	if (buffer[i])
		i++;
	j = 0;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	return (new_buffer);
}
