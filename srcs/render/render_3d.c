/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:08:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/16 21:24:05 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = (game->tex.ceiling[0] << 16) | (game->tex.ceiling[1] << 8)
		| game->tex.ceiling[2];
	floor_color = (game->tex.floor[0] << 16) | (game->tex.floor[1] << 8)
		| game->tex.floor[2];
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(&game->screen, x, y, ceil_color);
			else
				put_pixel(&game->screen, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	render_3d(t_game *game)
{
	int		x;
	t_ray	ray;

	draw_floor_ceiling(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		calc_step_side(game, &ray);
		run_dda(game, &ray);
		calc_wall_height(game, &ray);
		draw_wall_column(game, &ray, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
}
