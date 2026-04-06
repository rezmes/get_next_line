/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesgari <mmesgari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 12:43:09 by mmesgari          #+#    #+#             */
/*   Updated: 2026/01/08 14:09:05 by mmesgari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *string)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!string[i])
		return (NULL);
	while (string[i] && string[i] != '\n')
		i++;
	tmp = ft_substr(string, 0, i + 1);
	return (tmp);
}

char	*ft_stash(char *string)
{
	int		i;
	char	*tmp;

	i = 0;
	while (string[i] && string[i] != '\n')
		i++;
	if (!string[i])
	{
		free(string);
		return (NULL);
	}
	tmp = ft_substr(string, i + 1, ft_strlen(string));
	free(string);
	return (tmp);
}

char	*ft_read_fd(int fd, char *string)
{
	char	*buffer;
	int		res;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	res = 1;
	while (!ft_strchr(string, '\n') && res != 0)
	{
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == -1)
			return (free(buffer), free(string), NULL);
		buffer[res] = '\0';
		string = ft_strjoin(string, buffer);
	}
	free(buffer);
	return (string);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*string[1024];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	string[fd] = ft_read_fd(fd, string[fd]);
	if (!string[fd])
		return (NULL);
	line = ft_line(string[fd]);
	string[fd] = ft_stash(string[fd]);
	return (line);
}

#include <fcntl.h>
#include <stdio.h>


int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}