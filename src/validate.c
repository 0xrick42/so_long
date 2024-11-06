/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int check_rectangular(t_game *game)
{
    int i;
    int len;

    i = 0;
    while (i < game->map.height)
    {
        len = ft_strlen(game->map.grid[i]);
        if (len != game->map.width)
            return (0);
        i++;
    }
    return (1);
}

static int check_walls(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if ((y == 0 || y == game->map.height - 1 ||
                x == 0 || x == game->map.width - 1) &&
                game->map.grid[y][x] != '1')
                return (0);
            x++;
        }
        y++;
    }
    return (1);
}

static int check_path(t_game *game, int x, int y, char **visited)
{
    int collectibles;
    int found_exit;

    if (x < 0 || x >= game->map.width || y < 0 || y >= game->map.height
        || game->map.grid[y][x] == '1' || visited[y][x])
        return (0);

    visited[y][x] = 1;
    collectibles = (game->map.grid[y][x] == 'C');
    found_exit = (game->map.grid[y][x] == 'E');

    collectibles += check_path(game, x + 1, y, visited);
    collectibles += check_path(game, x - 1, y, visited);
    collectibles += check_path(game, x, y + 1, visited);
    collectibles += check_path(game, x, y - 1, visited);

    return (collectibles + found_exit);
}

static int validate_path(t_game *game)
{
    char    **visited;
    int     i;
    int     result;

    visited = malloc(sizeof(char *) * game->map.height);
    if (!visited)
        return (0);

    i = 0;
    while (i < game->map.height)
    {
        visited[i] = malloc(sizeof(char) * game->map.width);
        if (!visited[i])
        {
            while (--i >= 0)
                free(visited[i]);
            free(visited);
            return (0);
        }
        ft_memset(visited[i], 0, game->map.width);
        i++;
    }

    result = check_path(game, game->player.x, game->player.y, visited);

    i = 0;
    while (i < game->map.height)
        free(visited[i++]);
    free(visited);

    return (result == game->map.collectibles + 1);
}

static int check_characters(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            if (game->map.grid[y][x] == 'P')
            {
                game->player.x = x;
                game->player.y = y;
                game->map.start++;
            }
            else if (game->map.grid[y][x] == 'E')
                game->map.exit++;
            else if (game->map.grid[y][x] == 'C')
                game->map.collectibles++;
            else if (game->map.grid[y][x] != '0' && game->map.grid[y][x] != '1')
                return (0);
            x++;
        }
        y++;
    }
    return (game->map.start == 1 && game->map.exit == 1 && game->map.collectibles > 0);
}

int validate_map(t_game *game)
{
    if (!check_rectangular(game))
    {
        write(1, "Error\nMap is not rectangular\n", 28);
        return (0);
    }
    if (!check_walls(game))
    {
        write(1, "Error\nMap is not surrounded by walls\n", 35);
        return (0);
    }
    if (!check_characters(game))
    {
        write(1, "Error\nInvalid map characters or missing elements\n", 47);
        return (0);
    }
    if (!validate_path(game))
    {
        write(1, "Error\nNo valid path to collect all items and reach exit\n", 54);
        return (0);
    }
    return (1);
}
