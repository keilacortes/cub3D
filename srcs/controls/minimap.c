/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:35:12 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 20:36:31 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	put_pixel_img(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_player_direction(t_game *game)
{
	int		i;
	int		draw_x;
	int		draw_y;
	double	x;
	double	y;

	x = game->player.pos_x;
	y = game->player.pos_y;
	i = -1;
	while (++i < 35)
	{
		draw_x = MINIMAP_X + x * MINIMAP_SCALE + MINIMAP_SCALE / 2.0;
		draw_y = MINIMAP_Y + y * MINIMAP_SCALE + MINIMAP_SCALE / 2.0;
		if (i < 25)
			put_pixel_img(&game->screen, draw_x + (i % 5) - 2,
				draw_y + (i / 5) - 2, 0xFF0000);
		else
		{
			put_pixel_img(&game->screen, draw_x, draw_y, 0x90EE90);
			x += game->player.dir_x * 0.2;
			y += game->player.dir_y * 0.2;
		}
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
			put_pixel_img(&game->screen,
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
				draw_square(game, x, y, 0x7F00FF);
			else if (game->map.grid[y][x] == '0')
				draw_square(game, x, y, 0x555555);
			x++;
		}
		y++;
	}
	draw_player_direction(game);
}

int	game_loop(t_game *game)
{
	if (should_close_game())
		close_game(game);
	handle_movement(game);
	render_3d(game);
	draw_minimap(game);
	return (0);
}
