/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykhomsi <ykhomsi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:48:39 by ykhomsi           #+#    #+#             */
/*   Updated: 2024/11/12 22:14:32 by ykhomsi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TILE_SIZE 64
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

/* Key codes for Linux */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363

typedef struct s_player
{
	int			x;
	int			y;
	int			collectibles;
}				t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			collectibles;
	int			exit;
	int			start;
}				t_map;

typedef struct s_img
{
	void		*rick;
	void		*wall;
	void		*floor;
	void		*portal;
	void		*seed;
	int			width;
	int			height;
}				t_img;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		map;
	t_player	player;
	t_img		img;
	int			moves;
}				t_game;

/* Function Prototypes */
int				init_game(t_game *game);
int				load_map(t_game *game, char *file);
int				validate_map(t_game *game);
void			render_game(t_game *game);
int				handle_key(int keycode, t_game *game);
void			clean_exit(t_game *game, int status);
int				validate_path(t_game *game);
int				check_path(t_game *game, char **map);
void			flood_fill(t_game *game, char **map);
int				check_ex(char **map, int x, int y);
int				check_path_exit(t_game *game, char **map);

/* Utility functions */
size_t			ft_strlen(const char *s);
void			ft_bzero(void *s, size_t n);
void			player_pos(t_game *game, int x, int y);
char			**init_visited(t_game *game, int height);
char			*ft_strdup(char *s);

#endif
