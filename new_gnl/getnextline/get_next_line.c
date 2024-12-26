/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakkopru <fakkopru@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 05:30:41 by fakkopru          #+#    #+#             */
/*   Updated: 2024/12/24 16:15:28 by fakkopru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*first_remainder(int fd, char *remainder)
{
	char	*buffer;
	int		lenght;
	char	*temp;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	lenght = 1;
	while (lenght > 0)
	{
		lenght = read(fd, buffer, BUFFER_SIZE);
		if (lenght == -1)
			return (free(buffer), free(remainder), NULL);
		if (lenght == 0)
			break ;
		buffer[lenght] = '\0';
		temp = remainder;
		remainder = ft_strjoin(remainder, buffer);
		if (!remainder)
			return (free(buffer), free(temp), NULL);
		free(temp);
	}
	return (free(buffer), remainder);
}

char	*ft_get_line(char *remainder)
{
	char	*line;
	int		i;

	i = 0;
	if (remainder[i] == '\0')
		return (NULL);
	while (remainder[i] != '\0')
	{
		if (remainder[i] == '\n')
			break ;
		i++;
	}
	line = malloc(i + 2);
	if (!line)
	{
		free(remainder);
		return (NULL);
	}
	i = -1;
	while (remainder[++i] != '\n' && remainder[i] != '\0')
		line[i] = remainder[i];
	if (remainder[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_remainder(char *remainder)
{
	int		i;
	int		j;
	char	*new_remainder;

	i = 0;
	while (remainder[i] != '\0' && remainder[i] != '\n')
		i++;
	if (remainder[i] == '\0')
	{
		free(remainder);
		return (NULL);
	}
	new_remainder = malloc(ft_strlen(remainder) - i + 1);
	if (!new_remainder)
	{
		free(remainder);
		return (NULL);
	}
	i++;
	j = 0;
	while (remainder[i])
		new_remainder[j++] = remainder[i++];
	new_remainder[j] = '\0';
	free(remainder);
	return (new_remainder);
}

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!remainder)
	{
		remainder = malloc(BUFFER_SIZE + 1);
		if (!remainder)
			return (NULL);
		remainder[0] = '\0';
		remainder = first_remainder(fd, remainder);
		if (!remainder)
			return (NULL);
	}
	current_line = ft_get_line(remainder);
	if (!current_line)
		return (free(remainder), remainder = NULL, NULL);
	remainder = new_remainder(remainder);
	if (!remainder && current_line[0] == '\0')
		return (free(current_line), NULL);
	return (current_line);
}
