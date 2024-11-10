/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:47:44 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/09 02:48:11 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_path_exit(t_game *game, char **map)
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
			if (map[y][x] == 'E')
				return (check_ex(map, x, y));
			x++;
		}
		y++;
	}
	return (0);
}

int	check_ex(char **map, int x, int y)
{
	if (map[y][x + 1] == 'X')
		return (1);
	if (map[y][x - 1] == 'X')
		return (1);
	if (map[y - 1][x] == 'X')
		return (1);
	if (map[y + 1][x] == 'X')
		return (1);
	return (0);
}

void	fill(char **map, int x, int y)
{
	if (map[y][x] == '1' && map[y][x] != 'E')
		return ;
	if (map[y][x] != 'P' && map[y][x] != '0' && map[y][x] != 'C')
		return ;
	map[y][x] = 'X';
	fill(map, x + 1, y);
	fill(map, x - 1, y);
	fill(map, x, y + 1);
	fill(map, x, y - 1);
}

void	flood_fill(t_game *game, char **map)
{
	fill(map, game->player.x, game->player.y);
}
