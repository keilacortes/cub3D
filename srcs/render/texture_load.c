/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 21:14:13 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/16 21:16:23 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_one_texture(void *mlx, char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		exit(1);
	}
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
}

void	load_textures(t_game *game)
{
	load_one_texture(game->mlx, game->tex.north, &game->tex.no);
	load_one_texture(game->mlx, game->tex.south, &game->tex.so);
	load_one_texture(game->mlx, game->tex.west, &game->tex.we);
	load_one_texture(game->mlx, game->tex.east, &game->tex.ea);
}
