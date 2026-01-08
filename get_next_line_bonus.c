/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vblanco- <vblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:39:39 by vblanco-          #+#    #+#             */
/*   Updated: 2026/01/08 18:35:36 by vblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_stash_next(char *stash)
{
	int		s_len;
	int		index;
	char	*temp;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] != '\n')
	{
		free(stash);
		return (NULL);
	}
	s_len = ft_strlen(stash);
	temp = ft_substr(stash, index + 1, s_len - index);
	free(stash);
	return (temp);
}

char	*ft_line(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * i + 1);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_freejoin(char *buffer, char *stash, int s2len)
{
	char	*temp;

	temp = ft_strjoin(stash, buffer, s2len);
	free(stash);
	return (temp);
}

char	*ft_add_stash(int fd, char *stash)
{
	char	*buffer;
	int		i;

	if (stash == NULL)
		stash = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	i = 1;
	while (i > 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[i] = '\0';
		stash = ft_freejoin(buffer, stash, i);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	stash[fd] = ft_add_stash(fd, stash[fd]);
	if (stash[fd] == NULL || stash[fd][0] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	line = ft_line(stash[fd]);
	stash[fd] = ft_stash_next(stash[fd]);
	return (line);
}
