/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void put_image(t_game *game, void *img, int x, int y)
{
    mlx_put_image_to_window(game->mlx, game->win, img,
        x * TILE_SIZE, y * TILE_SIZE);
}

void render_game(t_game *game)
{
    int x;
    int y;

    y = 0;
    while (y < game->map.height)
    {
        x = 0;
        while (x < game->map.width)
        {
            put_image(game, game->img.floor, x, y);
            if (game->map.grid[y][x] == '1')
                put_image(game, game->img.wall, x, y);
            else if (game->map.grid[y][x] == 'P')
                put_image(game, game->img.rick, x, y);
            else if (game->map.grid[y][x] == 'E')
                put_image(game, game->img.portal, x, y);
            else if (game->map.grid[y][x] == 'C')
                put_image(game, game->img.seed, x, y);
            x++;
        }
        y++;
    }
}
