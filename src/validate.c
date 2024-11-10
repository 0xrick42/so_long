/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:49:02 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/09 02:49:43 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	player_pos(t_game *game, int x, int y)
{
	game->player.x = x;
	game->player.y = y;
	game->map.start++;
}

char	**init_visited(t_game *game, int height)
{
	char	**visited;
	int		i;

	i = 0;
	visited = malloc(sizeof(char *) * height);
	if (!visited)
		return (NULL);
	while (i < height)
	{
		visited[i] = ft_strdup(game->map.grid[i]);
		if (!visited[i])
		{
			while (i-- > 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	validate_path(t_game *game)
{
	char	**visited;
	int		result;
	int		i;

	i = 0;
	visited = init_visited(game, game->map.height);
	if (!visited)
		return (0);
	result = check_path(game, visited);
	while (i < game->map.height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (result);
}
