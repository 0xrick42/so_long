/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:48:39 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/10 16:07:00 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	initialize_game(int argc, t_game *game)
{
	if (argc != 2)
	{
		write(2, "Error\nUsage: ./so_long map.ber\n", 31);
		return (0);
	}
	if (!init_game(game))
		return (0);
	write(1, "Loading map...\n\n", 16);
	return (1);
}

static int	load_and_validate_map(t_game *game, char *map_path)
{
	if (!load_map(game, map_path))
	{
		clean_exit(game, EXIT_FAILURE);
		return (0);
	}
	if (!validate_map(game))
	{
		clean_exit(game, EXIT_FAILURE);
		return (0);
	}
	return (1);
}

static int	create_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "Rick and Morty: So Long");
	if (!game->win)
	{
		clean_exit(game, EXIT_FAILURE);
		return (0);
	}
	return (1);
}

static void	start_game_loop(t_game *game)
{
	mlx_key_hook(game->win, handle_key, game);
	mlx_hook(game->win, 17, 0, (void *)clean_exit, game);
	render_game(game);
	mlx_loop(game->mlx);
}

int	main(int argc, char **argv)
{
	t_game	game;
	size_t	len;

	if (argc != 2)
	{
		write(2, "Usage: ./so_long <map_file>\n", 28);
		return (EXIT_FAILURE);
	}
	len = ft_strlen(argv[1]);
	if (len <= 4 || argv[1][len - 4] != '.' || argv[1][len - 3] != 'b'
		|| argv[1][len - 2] != 'e' || argv[1][len - 1] != 'r')
	{
		write(2, "Error\nMap must be .ber file\n", 28);
		return (EXIT_FAILURE);
	}
	if (!initialize_game(argc, &game))
		return (EXIT_FAILURE);
	if (!load_and_validate_map(&game, argv[1]))
		return (EXIT_FAILURE);
	if (!create_window(&game))
		return (EXIT_FAILURE);
	start_game_loop(&game);
	return (EXIT_SUCCESS);
}
