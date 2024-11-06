/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void initialize_null(t_game *game)
{
    game->mlx = NULL;
    game->win = NULL;
    game->map.grid = NULL;
    game->img.rick = NULL;
    game->img.wall = NULL;
    game->img.floor = NULL;
    game->img.portal = NULL;
    game->img.seed = NULL;
}

static int load_images(t_game *game)
{
    game->img.width = TILE_SIZE;
    game->img.height = TILE_SIZE;

    if (!(game->img.rick = mlx_xpm_file_to_image(game->mlx, "textures/rick.xpm",
        &game->img.width, &game->img.height)))
    {
        write(2, "Error\nFailed to load rick.xpm\n", 29);
        return (0);
    }
    if (!(game->img.wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm",
        &game->img.width, &game->img.height)))
    {
        write(2, "Error\nFailed to load wall.xpm\n", 29);
        return (0);
    }
    if (!(game->img.floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm",
        &game->img.width, &game->img.height)))
    {
        write(2, "Error\nFailed to load floor.xpm\n", 30);
        return (0);
    }
    if (!(game->img.portal = mlx_xpm_file_to_image(game->mlx, "textures/portal.xpm",
        &game->img.width, &game->img.height)))
    {
        write(2, "Error\nFailed to load portal.xpm\n", 31);
        return (0);
    }
    if (!(game->img.seed = mlx_xpm_file_to_image(game->mlx, "textures/seed.xpm",
        &game->img.width, &game->img.height)))
    {
        write(2, "Error\nFailed to load seed.xpm\n", 29);
        return (0);
    }
    return (1);
}

int init_game(t_game *game)
{
    initialize_null(game);

    game->mlx = mlx_init();
    if (!game->mlx)
    {
        write(2, "Error\nFailed to initialize MLX\n", 30);
        return (0);
    }

    game->moves = 0;
    game->player.collectibles = 0;
    game->map.collectibles = 0;
    game->map.exit = 0;
    game->map.start = 0;

    if (!load_images(game))
    {
        write(2, "Error\nFailed to load images\n", 27);
        return (0);
    }
    return (1);
}
