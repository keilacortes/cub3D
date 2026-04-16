/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:08:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/16 16:31:27 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel(t_img *img, int x, int y, int color)
{
	char *dst;
	
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

static int	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	draw_floor_ceiling(t_game *game)
{
	int x;
	int y;
	int ceil_color;
	int floor_color;

	ceil_color = rgb(game->tex.ceiling[0], game->tex.ceiling[1], game->tex.ceiling[2]);
	floor_color = rgb(game->tex.floor[0], game->tex.floor[1], game->tex.floor[2]);
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

static void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	int y;
	int color;

	if (ray->side == 0)
		color = 0x00CCFF;
	else
		color = 0x009CC;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		put_pixel(&game->screen, x, y, color);
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
