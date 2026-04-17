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

static int	rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

static void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;
	int	ceil_color;
	int	floor_color;

	ceil_color = rgb(game->tex.ceiling[0], game->tex.ceiling[1],
			game->tex.ceiling[2]);
	floor_color = rgb(game->tex.floor[0], game->tex.floor[1],
			game->tex.floor[2]);
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

static t_img	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&game->tex.we);
		else
			return (&game->tex.ea);
	}
	else
	{
		if (ray->step_y > 0)
			return (&game->tex.no);
		else
			return (&game->tex.so);
	}
}

static void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	tex = get_texture(game, ray);
	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		tex_pos += step;
		color = *(int *)(tex->addr + (tex_y * tex->line_len + tex_x *
			(tex->bpp / 8)));
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
