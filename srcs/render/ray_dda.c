/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_dda.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/16 17:08:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/16 16:53:14 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char get_map_cell(t_game *game, int y, int x)
{
	size_t len;

	if (y < 0 || y >= game->map.height || !game->map.grid[y])
		return ('1');
	len = ft_strlen(game->map.grid[y]);
	if (x < 0 || (size_t)x >= len)
		return ('1');
	if (game->map.grid[y][x] == ' ')
		return ('1');
	return (game->map.grid[y][x]); 
}

static void	step_x(t_ray *ray)
{
	ray->side_dist_x += ray->delta_dist_x;
	ray->map_x += ray->step_x;
	ray->side = 0;
}

static void	step_y(t_ray *ray)
{
	ray->side_dist_y += ray->delta_dist_y;
	ray->map_y += ray->step_y;
	ray->side = 1;
}

void	run_dda(t_game *game, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
			step_x(ray);
		else
			step_y(ray);
		if (get_map_cell(game, ray->map_y, ray->map_x) == '1')
			ray->hit = 1;
	}
}
