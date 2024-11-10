/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:48:58 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/09 02:49:38 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	destroy_img(t_game *game)
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
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	game->mlx = NULL;
}

void	clean_exit(t_game *game, int status)
{
	int	i;

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
			destroy_img(game);
	}
	exit(status);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
}

char	*ft_strdup(char *s)
{
	size_t	i;
	size_t	size;
	char	*dup;

	i = 0;
	size = ft_strlen(s);
	dup = malloc(sizeof(char) * size + 1);
	if (dup == NULL)
		return (NULL);
	while (i < size)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
