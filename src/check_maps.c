/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_maps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:48:26 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/09 02:49:18 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	check_rectangular(t_game *game)
{
	int	i;
	int	len;

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

static int	check_walls(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if ((y == 0 || y == game->map.height - 1 || x == 0
					|| x == game->map.width - 1) && game->map.grid[y][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int	check_path(t_game *game, char **map)
{
	int	x;
	int	y;

	y = 0;
	flood_fill(game, map);
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (map[y][x] == 'C')
				return (0);
			x++;
		}
		y++;
	}
	return (check_path_exit(game, map));
}

static int	check_characters(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			if (game->map.grid[y][x] == 'P')
				player_pos(game, x, y);
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
	return (game->map.start == 1 && game->map.exit == 1
		&& game->map.collectibles > 0);
}

int	validate_map(t_game *game)
{
	if (!check_rectangular(game))
	{
		write(1, "Error\nMap is not rectangular\n", 29);
		return (0);
	}
	if (!check_walls(game))
	{
		write(1, "Error\nMap is not surrounded by walls\n", 37);
		return (0);
	}
	if (!check_characters(game))
	{
		write(1, "Error\nInvalid map characters or missing elements\n", 49);
		return (0);
	}
	if (!validate_path(game))
	{
		write(1, "Error\nNo valid path to collect all items and reach exit\n",
			56);
		return (0);
	}
	return (1);
}
