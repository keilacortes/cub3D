/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:35:12 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/07 12:00:58 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_direction(t_game *game)
{
	int		i;
	int		draw_x;
	int		draw_y;
	double	x;
	double	y;

	x = game->player.pos_x;
	y = game->player.pos_y;
	i = 0;
	while (i < 10)
	{
		draw_x = MINIMAP_X + x * MINIMAP_SCALE + MINIMAP_SCALE / 2.1;
		draw_y = MINIMAP_Y + y * MINIMAP_SCALE + MINIMAP_SCALE / 2.1;
		mlx_pixel_put(game->mlx, game->win, draw_x, draw_y, 0x90EE90);
		x += game->player.dir_x * 0.2;
		y += game->player.dir_y * 0.2;
		i++;
	}
}

static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			mlx_pixel_put(game->mlx, game->win,
				MINIMAP_X + x * MINIMAP_SCALE + j,
				MINIMAP_Y + y * MINIMAP_SCALE + i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			if (game->map.grid[y][x] == '1')
				draw_square(game, x, y, 0x7F00FF); // parede
			else if (game->map.grid[y][x] == '0')
				draw_square(game, x, y, 0x555555); // chão
			x++;
		}
		y++;
	}
	draw_player_direction(game);
	draw_square(game, (int)game->player.pos_x,
		(int)game->player.pos_y, 0xFF0000);
}

int	game_loop(t_game *game)
{
	handle_movement(game);
	// raycasting
	draw_minimap(game);
	return (0);
}

void	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
}
