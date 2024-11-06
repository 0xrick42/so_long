/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: assistant                                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 12:00:00                      #+#    #+#             */
/*   Updated: 2024/03/03 12:00:00                     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

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
    int     x;
    int     y;
    int     collectibles;
}   t_player;

typedef struct s_map
{
    char    **grid;
    int     width;
    int     height;
    int     collectibles;
    int     exit;
    int     start;
}   t_map;

typedef struct s_img
{
    void    *rick;
    void    *wall;
    void    *floor;
    void    *portal;
    void    *seed;
    int     width;
    int     height;
}   t_img;

typedef struct s_game
{
    void        *mlx;
    void        *win;
    t_map       map;
    t_player    player;
    t_img       img;
    int         moves;
}   t_game;

/* Function Prototypes */
int     init_game(t_game *game);
int     load_map(t_game *game, char *file);
int     validate_map(t_game *game);
void    render_game(t_game *game);
int     handle_key(int keycode, t_game *game);
void    clean_exit(t_game *game, int status);

/* Utility functions */
size_t  ft_strlen(const char *s);
void    ft_bzero(void *s, size_t n);
void    *ft_memset(void *b, int c, size_t len);

#endif
