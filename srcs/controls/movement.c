/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:35:38 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 20:39:05 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

static int	is_blocked(t_game *game, double x, double y)
{
	int		row;
	int		col;
	size_t	len;

	row = (int)y;
	col = (int)x;
	if (row < 0 || row >= game->map.height || !game->map.grid[row])
		return (1);
	len = ft_strlen(game->map.grid[row]);
	if (col < 0 || (size_t)col >= len)
		return (1);
	if (game->map.grid[row][col] == '1' || game->map.grid[row][col] == ' ')
		return (1);
	return (0);
}

static void	move_player(t_game *game, double dir_x, double dir_y, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + dir_x * speed;
	new_y = game->player.pos_y + dir_y * speed;
	if (!is_blocked(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (!is_blocked(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

static double	get_frame_scale(void)
{
	static struct timeval	last;
	struct timeval			now;
	double					delta;

	gettimeofday(&now, NULL);
	if (last.tv_sec == 0 && last.tv_usec == 0)
	{
		last = now;
		return (1.0);
	}
	delta = (now.tv_sec - last.tv_sec);
	delta += (now.tv_usec - last.tv_usec) / 1000000.0;
	last = now;
	if (delta < 0.001)
		delta = 0.001;
	if (delta > 0.05)
		delta = 0.05;
	return (delta * 60.0);
}

static void	rotate(t_game *game, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(angle)
		- game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle)
		+ game->player.dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle)
		- game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle)
		+ game->player.plane_y * cos(angle);
}

void	handle_movement(t_game *game)
{
	double	scale;
	double	speed;

	scale = get_frame_scale();
	speed = MOVE_SPEED * scale;
	if ((game->player.keys.w || game->player.keys.s)
		&& (game->player.keys.a || game->player.keys.d))
		speed *= 0.70710678118;
	if (game->player.keys.w)
		move_player(game, game->player.dir_x, game->player.dir_y, speed);
	if (game->player.keys.s)
		move_player(game, -game->player.dir_x, -game->player.dir_y, speed);
	if (game->player.keys.a)
		move_player(game, game->player.dir_y, -game->player.dir_x, speed);
	if (game->player.keys.d)
		move_player(game, -game->player.dir_y, game->player.dir_x, speed);
	if (game->player.keys.left)
		rotate(game, -ROT_SPEED * scale);
	if (game->player.keys.right)
		rotate(game, ROT_SPEED * scale);
}
