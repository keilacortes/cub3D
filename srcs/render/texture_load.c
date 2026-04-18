/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 21:14:13 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 20:00:19 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	texture_error(t_game *game, char *path)
{
	ft_putstr_fd("Error\nFailed to load texture: ", 2);
	ft_putendl_fd(path, 2);
	cleanup_game(game);
	exit(1);
}

static void	load_one_texture(t_game *game, char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		texture_error(game, path);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (!tex->addr)
		texture_error(game, path);
}

void	load_textures(t_game *game)
{
	load_one_texture(game, game->tex.north, &game->tex.no);
	load_one_texture(game, game->tex.south, &game->tex.so);
	load_one_texture(game, game->tex.west, &game->tex.we);
	load_one_texture(game, game->tex.east, &game->tex.ea);
}
