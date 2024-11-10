/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:48:35 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/09 02:49:24 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	initialize_null(t_game *game)
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

int	xpm_to_img(t_game *game, void **img_ptr, char *file_path)
{
	int	img_w;
	int	img_h;

	img_w = TILE_SIZE;
	img_h = TILE_SIZE;
	*img_ptr = mlx_xpm_file_to_image(game->mlx, file_path, &img_w, &img_h);
	if (!*img_ptr)
	{
		write(2, "Error\nFailed to load image\n", 27);
		return (0);
	}
	return (1);
}

int	load_images(t_game *game)
{
	if (!xpm_to_img(game, (void **)&game->img.rick, "textures/rick.xpm")
		|| !xpm_to_img(game, (void **)&game->img.wall, "textures/wall.xpm")
		|| !xpm_to_img(game, (void **)&game->img.floor, "textures/floor.xpm")
		|| !xpm_to_img(game, (void **)&game->img.portal, "textures/portal.xpm")
		|| !xpm_to_img(game, (void **)&game->img.seed, "textures/seed.xpm"))
	{
		return (0);
	}
	return (1);
}

int	init_game(t_game *game)
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
