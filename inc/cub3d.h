/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 18:03:19 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/03/27 14:42:01 by kqueiroz         ###   ########.fr       */
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
	int		width;
	int		height;
}	t_map;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
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
void	check_arg(char *arg, t_game *game);
void	parse_file(const char *file, t_game *game);
//utils parse
void	free_split(char **arr);
int		is_valid_num(char *str);
char	*get_value(char *line);

#endif