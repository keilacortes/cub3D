/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/06 19:35:23 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/16 21:32:41 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int key, t_game *game)
{
	if (key == KEY_ESC)
		close_game(game);
	if (key == KEY_W)
		game->player.keys.w = 1;
	if (key == KEY_S)
		game->player.keys.s = 1;
	if (key == KEY_A)
		game->player.keys.a = 1;
	if (key == KEY_D)
		game->player.keys.d = 1;
	if (key == KEY_LEFT)
		game->player.keys.left = 1;
	if (key == KEY_RIGHT)
		game->player.keys.right = 1;
	return (0);
}

static int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->player.keys.w = 0;
	if (key == KEY_S)
		game->player.keys.s = 0;
	if (key == KEY_A)
		game->player.keys.a = 0;
	if (key == KEY_D)
		game->player.keys.d = 0;
	if (key == KEY_LEFT)
		game->player.keys.left = 0;
	if (key == KEY_RIGHT)
		game->player.keys.right = 0;
	return (0);
}

void	setup_hooks(t_game *game)
{
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_loop_hook(game->mlx, game_loop, game);
}
