/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:48:45 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/10 16:30:47 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	process_map_line(char c, int *width, int *max_width, int *height)
{
	if (c == '\n')
	{
		(*height)++;
		if (*width > *max_width)
			*max_width = *width;
		*width = 0;
	}
	else
		(*width)++;
	return (1);
}

static int	count_map_dimensions(int fd, int *max_width, int *height)
{
	char	c;
	int		width;
	int		ret;

	width = 0;
	*height = 0;
	*max_width = 0;
	ret = read(fd, &c, 1);
	if (ret <= 0)
	{
		write(2, "Error\nMap is empty\n", 19);
		return (0);
	}
	while (ret > 0)
	{
		process_map_line(c, &width, max_width, height);
		ret = read(fd, &c, 1);
	}
	if (width > 0)
	{
		(*height)++;
		if (width > *max_width)
			*max_width = width;
	}
	return (*height > 0 && *max_width > 0);
}

static int	get_map_size(char *file, t_game *game)
{
	int	fd;
	int	max_width;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\n", 6);
		return (0);
	}
	if (!count_map_dimensions(fd, &max_width, &game->map.height))
	{
		close(fd);
		return (0);
	}
	game->map.width = max_width;
	close(fd);
	return (1);
}

static char	*read_line(int fd)
{
	char	*line;
	int		i;
	char	c;
	int		bytes;

	line = malloc(sizeof(char) * 1024);
	if (!line)
		return (NULL);
	i = 0;
	bytes = read(fd, &c, 1);
	while (bytes > 0 && c != '\n' && i < 1023)
	{
		line[i] = c;
		i++;
		bytes = read(fd, &c, 1);
	}
	if (bytes <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	line[i] = '\0';
	return (line);
}

int	load_map(t_game *game, char *file)
{
	int	fd;
	int	i;

	if (!get_map_size(file, game))
		return (0);
	game->map.grid = malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (write(2, "Error\n", 6), 0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (free(game->map.grid), write(2, "Error\n", 6), 0);
	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = read_line(fd);
		if (!game->map.grid[i])
		{
			while (--i >= 0)
				free(game->map.grid[i]);
			return (free(game->map.grid), close(fd), write(2, "Error\n", 6), 0);
		}
		i++;
	}
	return (game->map.grid[i] = NULL, close(fd), 1);
}
