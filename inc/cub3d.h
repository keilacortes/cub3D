/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:03:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/05 08:50:51 by kqueiroz         ###   ########.fr       */
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