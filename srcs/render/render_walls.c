/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:46:45 by loena             #+#    #+#             */
/*   Updated: 2026/04/18 14:35:29 by loda-sil         ###   ########.fr       */
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

static t_img	*get_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x > 0)
			return (&game->tex.we);
		return (&game->tex.ea);
	}
	if (ray->step_y > 0)
		return (&game->tex.so);
	return (&game->tex.no);
}

static double	get_wall_x(t_game *game, t_ray *ray)
{
	double	wall_x;

	if (ray->side == 0)
		wall_x = game->player.pos_y + ray->perp_dist * ray->ray_dir_y;
	else
		wall_x = game->player.pos_x + ray->perp_dist * ray->ray_dir_x;
	return (wall_x - floor(wall_x));
}

static void	draw_tex_pixels(t_game *game, t_ray *ray, t_img *tex, int pos[2])
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		if (tex_y >= tex->height)
			tex_y = tex->height - 1;
		tex_pos += step;
		color = *(int *)(tex->addr + (tex_y * tex->line_len + pos[1]
					* (tex->bpp / 8)));
		put_pixel(&game->screen, pos[0], y, color);
		y++;
	}
}

void	draw_wall_column(t_game *game, t_ray *ray, int x)
{
	t_img	*tex;
	double	wall_x;
	int		pos[2];

	tex = get_texture(game, ray);
	wall_x = get_wall_x(game, ray);
	pos[0] = x;
	pos[1] = (int)(wall_x * tex->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		pos[1] = tex->width - pos[1] - 1;
	draw_tex_pixels(game, ray, tex, pos);
}
