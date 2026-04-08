/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:03:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/06 22:30:31 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define SCREEN_W 800
# define SCREEN_H 600

# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_ESC 65307

# define NORTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
}	t_textures;

typedef struct s_map
{
	char	**grid;
	char	spawn;
	int		height;
}	t_map;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
	int	spawn_found;
}	t_player;

typedef struct s_img
{
	void *img;
	int *data;
	int width;
	int height;
} t_img;

typedef struct s_camera
{
	double x;
	double y;
	double angle;
	double fov;
} t_camera;

typedef struct s_render
{
	void *mlx;
	void *win;
	void *img;
	int *data;
	int size_line;
	int bpp;
	int endian;
	t_img textures[4];
}	t_render;

typedef struct s_game
{
	t_map		map;
	t_textures	tex;
	t_player	player;
	t_camera	camera;
	t_render	rend;
} t_game;

void	exit_error(char *message);
void	free_grid(char **arr);
void	cleanup_game(t_game *game);
void	check_arg(char *arg, t_game *game);
void	parse_file(const char *file, t_game *game);
//utils parse
int		is_valid_num(char *str);
char	*get_value(char *line);
//parse_map
void	parse_map(const char *file, t_map *map, t_player *player);
void	validate_map(t_map *map, t_player *player);

#endif
