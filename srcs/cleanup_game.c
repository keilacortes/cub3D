/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 08:47:03 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/16 21:31:37 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->tex.no.img)
		mlx_destroy_image(game->mlx, game->tex.no.img);
	if (game->tex.so.img)
		mlx_destroy_image(game->mlx, game->tex.so.img);
	if (game->tex.we.img)
		mlx_destroy_image(game->mlx, game->tex.we.img);
	if (game->tex.ea.img)
		mlx_destroy_image(game->mlx, game->tex.ea.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int	close_game(t_game *game)
{
	cleanup_game(game);
	exit(0);
	return (0);
}
