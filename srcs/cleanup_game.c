/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_game.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/05 08:47:03 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 19:59:44 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_tex_paths(t_textures *tex)
{
	if (tex->north)
	{
		free(tex->north);
		tex->north = NULL;
	}
	if (tex->south)
	{
		free(tex->south);
		tex->south = NULL;
	}
	if (tex->west)
	{
		free(tex->west);
		tex->west = NULL;
	}
	if (tex->east)
	{
		free(tex->east);
		tex->east = NULL;
	}
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return ;
	if (game->map.grid)
	{
		free_grid(game->map.grid);
		game->map.grid = NULL;
	}
	free_tex_paths(&game->tex);
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
