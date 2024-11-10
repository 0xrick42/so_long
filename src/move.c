/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:48:50 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/10 15:55:50 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	can_move(t_game *game, int new_x, int new_y)
{
	char	pos;

	pos = game->map.grid[new_y][new_x];
	if (pos == '1')
		return (0);
	if (pos == 'E' && game->player.collectibles != game->map.collectibles)
		return (0);
	return (1);
}

static void	print_moves(int moves)
{
	char	num[12];
	int		i;
	int		n;

	n = moves;
	i = 0;
	if (n == 0)
		num[i++] = '0';
	while (n > 0)
	{
		num[i++] = (n % 10) + '0';
		n /= 10;
	}
	num[i] = '\0';
	while (--i >= 0)
		write(1, &num[i], 1);
	write(1, "\n", 1);
}

static int	update_move(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'C')
		game->player.collectibles++;
	else if (game->map.grid[new_y][new_x] == 'E')
	{
		if (game->player.collectibles == game->map.collectibles)
		{
			game->map.grid[game->player.y][game->player.x] = '0';
			game->map.grid[new_y][new_x] = 'P';
			game->player.x = new_x;
			game->player.y = new_y;
			game->moves++;
			write(1, "Moves: ", 7);
			print_moves(game->moves);
			write(1, "\nWubba Lubba Dub Dub! You've won!\n", 34);
			clean_exit(game, EXIT_SUCCESS);
		}
		return (0);
	}
	game->map.grid[game->player.y][game->player.x] = '0';
	game->map.grid[new_y][new_x] = 'P';
	game->player.x = new_x;
	game->player.y = new_y;
	return (1);
}

static int	try_move(t_game *game, int dx, int dy)
{
	int	new_x;
	int	new_y;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	if (new_x >= 0 && new_x < game->map.width && new_y >= 0
		&& new_y < game->map.height)
	{
		if (can_move(game, new_x, new_y))
			return (update_move(game, new_x, new_y));
	}
	return (0);
}

int	handle_key(int keycode, t_game *game)
{
	int	moved;

	moved = 0;
	if (keycode == KEY_ESC)
		clean_exit(game, EXIT_SUCCESS);
	else if (keycode == KEY_W || keycode == KEY_UP)
		moved = try_move(game, 0, -1);
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		moved = try_move(game, 0, 1);
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		moved = try_move(game, -1, 0);
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		moved = try_move(game, 1, 0);
	if (moved)
	{
		game->moves++;
		write(1, "Moves: ", 7);
		print_moves(game->moves);
		render_game(game);
	}
	return (0);
}
