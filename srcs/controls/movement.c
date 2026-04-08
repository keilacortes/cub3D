/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:35:38 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/07 15:41:22 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward_back(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * speed;
	new_y = game->player.pos_y + game->player.dir_y * speed;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
}

static void	move_side(t_game *game, double speed)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * speed;
	new_y = game->player.pos_y - game->player.dir_x * speed;
	if (game->map.grid[(int)game->player.pos_y][(int)new_x] != '1')
		game->player.pos_x = new_x;
	if (game->map.grid[(int)new_y][(int)game->player.pos_x] != '1')
		game->player.pos_y = new_y;
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
	if (game->player.keys.w)
		move_forward_back(game, MOVE_SPEED);
	if (game->player.keys.s)
		move_forward_back(game, -MOVE_SPEED);
	if (game->player.keys.a)
		move_side(game, -MOVE_SPEED);
	if (game->player.keys.d)
		move_side(game, MOVE_SPEED);
	if (game->player.keys.left)
		rotate(game, -ROT_SPEED);
	if (game->player.keys.right)
		rotate(game, ROT_SPEED);
}
