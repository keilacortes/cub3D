/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 08:47:03 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/07 16:36:20 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	cleanup_game(t_game *game)
{
	if (game->map.grid)
		free_grid(game->map.grid);
	if (game->tex.north)
		free(game->tex.north);
	if (game->tex.south)
		free(game->tex.south);
	if (game->tex.west)
		free(game->tex.west);
	if (game->tex.east)
		free(game->tex.east);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	exit (0);
	return (0);
}
