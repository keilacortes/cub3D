/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 22:09:53 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/15 22:13:39 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}
void	render_3d(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&game->screen, x, y,
					rgb(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2]));
			else
				put_pixel(&game->screen, x, y,
					rgb(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2]));
			x++;
		}
		y++;
	}
	y = HEIGHT / 4;
	while (y < (HEIGHT * 3) / 4)
	{
		put_pixel(&game->screen, WIDTH / 2, y, 0xFFFFFF);
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
