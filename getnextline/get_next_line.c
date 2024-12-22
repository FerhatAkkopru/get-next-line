/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fakkopru <fakkopru@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 05:30:41 by fakkopru          #+#    #+#             */
/*   Updated: 2024/12/22 05:31:28 by fakkopru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char    *ft_check_nl(char *s)
{
    int i;

    i = 0;
    if (!s)
        return (NULL);
    while (s[i])
    {
        if (s[i] == '\n')
            return (s + i);
        i++;
    }
    return (NULL);
}

char    *first_remainder(int fd, char *remainder)
{
    char *buffer;
    int lenght;

    buffer = malloc(BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);

    lenght = 1;
    while (lenght != 0 && !ft_check_nl(remainder))
    {
        lenght = read(fd, buffer, BUFFER_SIZE);
        if (lenght == -1)
        {
            free(buffer);
            free(remainder);
            return (NULL);
        }
        buffer[lenght] = '\0';
        remainder = ft_strjoin(remainder, buffer);
    }
    free(buffer);
    return (remainder);
}

char *get_line(char *remainder)
{
    char *line;
    int i;

    i = 0;
    if (remainder[i] == '\0')
        return (NULL);

    while (remainder[i] != '\0')
    {
        if (remainder[i] == '\n')
            break;
        i++;
    }

    line = malloc(i + 1);
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

char *new_remainder(char *remainder)
{
    int i;
    int j;
    char *new_remainder;

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

char    *get_next_line(int fd)
{
    static char *remainder;
    char *current_line;

    if (fd < 0 || BUFFER_SIZE <= 0)
    {
        free(remainder);
        return (NULL);
    }

    remainder = first_remainder(fd, remainder);
    if (!remainder)
        return (NULL);
    
    current_line = get_line(remainder);
    remainder = new_remainder(remainder);
    return (current_line);
}