/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 22:07:44 by loena             #+#    #+#             */
/*   Updated: 2026/04/06 22:36:10 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void init_render(t_game *game)
{
	game->rend.mlx = mlx_init();
	if (!game->rend.mlx)
		exit_error("Failed to inicialize MLX");
	game->rend.win = mlx_new_window(game->rend.mlx,
		SCREEN_W, SCREEN_H, "Cub3d");
	if (!game->rend.win)
		exit_error("Failed to create window");
	game->rend.img = mlx_new_image(game->rend.mlx, SCREEN_W, SCREEN_H);
	if (!game->rend.img)
		exit_error("Failed to create image");
	game->rend.img_data = (int *)mlx_get_data_addr(game->rend.img, &game->rend->bpp, &game->rend->size_line, &game->rend->endian);
}

static void	load_single_texture(t_game *game, int index, char *path)
{
	int bpp;
	int size_line;
	int endian;
}
