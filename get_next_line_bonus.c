/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vblanco- <vblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:39:39 by vblanco-          #+#    #+#             */
/*   Updated: 2026/01/09 18:11:12 by vblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_stash_next(char *stash)
{
	int		s_len;
	int		index;
	char	*temp;

	index = 0;
	if (!stash)
		return (free(stash), NULL);
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] != '\n')
		return (free(stash), NULL);
	s_len = ft_strlen(stash);
	temp = ft_substr(stash, index + 1, s_len - index);
	return (free(stash), temp);
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
	line = malloc(sizeof(char) * (i + 1));
	if (line == NULL)
		return (free(line), free(stash), NULL);
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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*str;
	const unsigned char	*in;

	in = (const unsigned char *) src;
	str = (unsigned char *) dest;
	while (n > 0)
	{
		*str++ = (unsigned char)*in;
		in++;
		n--;
	}
	return (dest);
}

char	*ft_add_stash(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	int		i_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (NULL);
	i_read = 1;
	while (i_read > 0)
	{
		i_read = read(fd, buffer, BUFFER_SIZE);
		if (i_read == -1)
			return (free(stash), free(buffer), NULL);
		if (i_read == 0)
			break ;
		buffer[i_read] = '\0';
		temp = ft_strjoin(stash, buffer, i_read);
		free(stash);
		stash = temp;
		if (!stash)
			return (free(buffer), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (free(buffer), stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
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
