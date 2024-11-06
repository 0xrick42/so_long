/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
    {
        write(2, "Error\nUsage: ./so_long map.ber\n", 31);
        return (EXIT_FAILURE);
    }
    if (!init_game(&game))
        return (EXIT_FAILURE);

    write(1, "Loading map...\n", 14);
    if (!load_map(&game, argv[1]))
    {
        clean_exit(&game, EXIT_FAILURE);
        return (EXIT_FAILURE);
    }

    if (!validate_map(&game))
    {
        clean_exit(&game, EXIT_FAILURE);
        return (EXIT_FAILURE);
    }

    game.win = mlx_new_window(game.mlx, game.map.width * TILE_SIZE,
        game.map.height * TILE_SIZE, "Rick and Morty: So Long");
    if (!game.win)
    {
        clean_exit(&game, EXIT_FAILURE);
        return (EXIT_FAILURE);
    }

    mlx_key_hook(game.win, handle_key, &game);
    mlx_hook(game.win, 17, 0, (void *)clean_exit, &game);
    render_game(&game);
    mlx_loop(game.mlx);
    return (EXIT_SUCCESS);
}
