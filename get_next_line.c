/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vblanco- <vblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:39:39 by vblanco-          #+#    #+#             */
/*   Updated: 2026/01/09 18:10:05 by vblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	size_t	index;
	char	*line;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] == '\n')
		index++;
	line = malloc(sizeof(char) * (index + 1));
	if (line == NULL)
		return (free(line), free(stash), NULL);
	index = 0;
	while (stash[index] && stash[index] != '\n')
	{
		line[index] = stash[index];
		index++;
	}
	if (stash[index] == '\n')
		line[index++] = '\n';
	line[index] = '\0';
	return (line);
}

char	*ft_add_stash(int fd, char *stash)
{
	char	*buffer;
	char	*temp;
	int		i_read;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i_read = 1;
	while (i_read > 0)
	{
		i_read = read(fd, buffer, BUFFER_SIZE);
		if (i_read == -1)
			return (free(buffer), free(stash), NULL);
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
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = ft_add_stash(fd, stash);
	if (stash == NULL || stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_line(stash);
	stash = ft_stash_next(stash);
	return (line);
}

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
	printf("BUFFER-SIZE : %d", BUFFER_SIZE);
    close(fd);
    return (0);
}
