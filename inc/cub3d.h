/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:03:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/07 16:38:22 by kqueiroz         ###   ########.fr       */
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

# define KEY_W		119
# define KEY_A		100
# define KEY_S		115
# define KEY_D		97
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_ESC	65307

# define MOVE_SPEED		1
# define ROT_SPEED		1
# define MINIMAP_SCALE	10
# define MINIMAP_X		10
# define MINIMAP_Y		10

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

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		spawn_found;
	t_keys	keys;
}	t_player;

typedef struct s_game
{
	t_map		map;
	t_textures	tex;
	t_player	player;
	void		*mlx;
	void		*win;
}	t_game;

void	exit_error(char *message);
void	free_grid(char **arr);
int		cleanup_game(t_game *game);
void	check_arg(char *arg, t_game *game);
void	parse_file(const char *file, t_game *game);
//utils parse
int		is_valid_num(char *str);
char	*get_value(char *line);
//parse_map
void	parse_map(const char *file, t_map *map, t_player *player);
void	validate_map(t_map *map, t_player *player);
void	check_file_tex(t_textures *tex);
// controls
	void	setup_hooks(t_game *game);
	int		game_loop(t_game *game);
	void	handle_movement(t_game *game);
	void	draw_minimap(t_game *game);
#endif
