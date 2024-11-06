/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int get_map_size(char *file, t_game *game)
{
    int     fd;
    char    c;
    int     width;
    int     max_width;

    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    game->map.height = 0;
    width = 0;
    max_width = 0;
    while (read(fd, &c, 1) > 0)
    {
        if (c == '\n')
        {
            game->map.height++;
            if (width > max_width)
                max_width = width;
            width = 0;
        }
        else
            width++;
    }
    if (width > 0)
    {
        game->map.height++;
        if (width > max_width)
            max_width = width;
    }
    game->map.width = max_width;
    close(fd);
    return (game->map.height > 0 && max_width > 0);
}

static char *read_line(int fd)
{
    char    *line;
    int     i;
    char    c;
    int     bytes;

    line = malloc(sizeof(char) * 1024);
    if (!line)
        return (NULL);
    i = 0;
    while ((bytes = read(fd, &c, 1)) > 0 && c != '\n')
        line[i++] = c;
    if (bytes <= 0 && i == 0)
    {
        free(line);
        return (NULL);
    }
    line[i] = '\0';
    return (line);
}

int load_map(t_game *game, char *file)
{
    int     fd;
    int     i;

    if (!get_map_size(file, game))
        return (0);

    game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
    if (!game->map.grid)
        return (0);

    fd = open(file, O_RDONLY);
    if (fd < 0)
    {
        free(game->map.grid);
        game->map.grid = NULL;
        return (0);
    }

    i = 0;
    while (i < game->map.height)
    {
        game->map.grid[i] = read_line(fd);
        if (!game->map.grid[i])
        {
            while (--i >= 0)
                free(game->map.grid[i]);
            free(game->map.grid);
            game->map.grid = NULL;
            close(fd);
            return (0);
        }
        i++;
    }
    game->map.grid[i] = NULL;
    close(fd);
    return (1);
}

/* Utility functions */
size_t ft_strlen(const char *s)
{
    size_t i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

void ft_bzero(void *s, size_t n)
{
    unsigned char *ptr;

    ptr = (unsigned char *)s;
    while (n--)
        *ptr++ = 0;
}

void *ft_memset(void *b, int c, size_t len)
{
    unsigned char *ptr;

    ptr = (unsigned char *)b;
    while (len--)
        *ptr++ = (unsigned char)c;
    return (b);
}
