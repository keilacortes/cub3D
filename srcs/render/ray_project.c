/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_project.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:08:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/16 16:39:57 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	clamp_draw_limits(t_ray *ray)
{
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	calc_wall_height(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - game->player.pos_x + (1 - ray->step_x) / 2.0)
			/ ray->ray_dir_x;
	else
		ray->perp_dist = (ray->map_y - game->player.pos_y + (1 - ray->step_y) / 2.0)
			/ ray->ray_dir_x;
	if (ray->perp_dist < 0.001)
		ray->perp_dist = 0.001;
	ray->line_height = (int)(HEIGHT / ray->perp_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	clamp_draw_limits(ray);
}
