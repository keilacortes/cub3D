/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:03:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 20:41:39 by loda-sil         ###   ########.fr       */
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

# define WIDTH			800
# define HEIGHT			600

# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_ESC	65307

# define MOVE_SPEED		0.05
# define ROT_SPEED		0.05
# define MINIMAP_SCALE	10
# define MINIMAP_X		10
# define MINIMAP_Y		10

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	int		floor[3];
	int		ceiling[3];
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
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
	t_img		screen;
	void		*mlx;
	void		*win;
}	t_game;

typedef struct s_ray
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

void	exit_error(char *message);
void	exit_error_game(t_game *game, char *message);
void	free_grid(char **arr);
void	cleanup_game(t_game *game);
int		close_game(t_game *game);
void	check_arg(char *arg, t_game *game);
void	parse_file(const char *file, t_game *game);
int		is_valid_num(char *str);
char	*get_value(char *line);
void	parse_map(const char *file, t_game *game);
int		player_pos(t_player *player, char c, int x, int y);
void	validate_map(t_game *game);
void	check_file_tex(t_textures *tex);
void	setup_hooks(t_game *game);
int		game_loop(t_game *game);
void	setup_signal_handlers(void);
int		should_close_game(void);
int		parse_element_line(t_game *game, char *line);
int		set_texture(char **slot, char *line);
int		parse_color(char *str, int *rgb);
int		is_map_or_empty_line(char *line);
void	handle_movement(t_game *game);
void	draw_minimap(t_game *game);
void	render_3d(t_game *game);
void	init_ray(t_game *game, t_ray *ray, int x);
void	calc_step_side(t_game *game, t_ray *ray);
void	run_dda(t_game *game, t_ray *ray);
void	calc_wall_height(t_game *game, t_ray *ray);
void	draw_wall_column(t_game *game, t_ray *ray, int x);
void	load_textures(t_game *game);

#endif
