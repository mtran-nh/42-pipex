/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtran-nh <mtran-nh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 19:05:34 by mtran-nh          #+#    #+#             */
/*   Updated: 2025/09/23 19:05:48 by mtran-nh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*read_until_nl(int fd, char *remain)
{
	char	buf[BUFFER_SIZE + 1];
	char	*result;
	char	*tmp;
	int		bytes;

	result = ft_strdup(remain);
	if (!result)
		return (NULL);
	remain[0] = '\0';
	bytes = 1;
	while (!ft_strchr(result, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		buf[bytes] = '\0';
		tmp = result;
		result = ft_strjoin(tmp, buf);
		free(tmp);
		if (!result)
			return (NULL);
	}
	return (result);
}

static void	new_remain(char *remain, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	while (line[i] && j < BUFFER_SIZE)
		remain[j++] = line[i++];
	remain[j] = '\0';
}

static char	*extract_line(char *buffer)
{
	int		len;
	char	*line;
	int		i;

	len = 0;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = -1;
	while (++i < len)
		line[i] = buffer[i];
	line[len] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	remain[BUFFER_SIZE + 1];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_until_nl(fd, remain);
	if (!buffer)
		return (NULL);
	new_remain(remain, buffer);
	line = extract_line(buffer);
	free(buffer);
	return (line);
}
