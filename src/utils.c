/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void clean_exit(t_game *game, int status)
{
    int i;

    if (game)
    {
        if (game->map.grid)
        {
            i = 0;
            while (i < game->map.height && game->map.grid[i])
            {
                free(game->map.grid[i]);
                game->map.grid[i] = NULL;
                i++;
            }
            free(game->map.grid);
            game->map.grid = NULL;
        }

        if (game->mlx)
        {
            if (game->img.rick)
                mlx_destroy_image(game->mlx, game->img.rick);
            if (game->img.wall)
                mlx_destroy_image(game->mlx, game->img.wall);
            if (game->img.floor)
                mlx_destroy_image(game->mlx, game->img.floor);
            if (game->img.portal)
                mlx_destroy_image(game->mlx, game->img.portal);
            if (game->img.seed)
                mlx_destroy_image(game->mlx, game->img.seed);

            if (game->win)
            {
                mlx_destroy_window(game->mlx, game->win);
                game->win = NULL;
            }

            #ifdef __linux__
            mlx_destroy_display(game->mlx);
            #endif
            free(game->mlx);
            game->mlx = NULL;
        }
    }
    exit(status);
}
