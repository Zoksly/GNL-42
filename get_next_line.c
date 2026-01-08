/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vblanco- <vblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 19:39:39 by vblanco-          #+#    #+#             */
/*   Updated: 2026/01/08 19:26:05 by vblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	size_t	index;
	char	*line;

	index = 0;
	while (stash[index] && stash[index] != '\n')
		index++;
	if (stash[index] == '\n')
		index++;
	line = malloc(sizeof(char) * index + 1);
	if (line == NULL)
	{
		free(line);
		free (stash);
		return (NULL);
	}
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
	int		i_read;

	if (stash == NULL)
		stash = ft_strdup("");
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	i_read = 1;
	while (i_read > 0)
	{
		i_read = read(fd, buffer, BUFFER_SIZE);
		if (i_read == -1)
		{
			free(buffer);
			free(stash);
			return (NULL);
		}
		buffer[i_read] = '\0';
		stash = ft_freejoin(buffer, stash, i_read);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
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

/* int main(void)
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
} */
