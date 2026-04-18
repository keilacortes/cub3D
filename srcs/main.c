/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:51:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 19:54:07 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_player(t_player *player)
{
	player->spawn_found = 0;
	player->pos_x = 0;
	player->pos_y = 0;
	player->dir_x = 0;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = 0;
	player->keys.a = 0;
	player->keys.d = 0;
	player->keys.s = 0;
	player->keys.w = 0;
	player->keys.left = 0;
	player->keys.right = 0;
}

static void	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		exit_error_game(game, "mlx_init failed");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		exit_error_game(game, "mlx_new_window failed");
	game->screen.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen.img)
		exit_error_game(game, "mlx_new_image failed");
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	if (!game->screen.addr)
		exit_error_game(game, "mlx_get_data_addr failed");
}

static void	init_img(t_img *img)
{
	img->img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
	img->width = 0;
	img->height = 0;
}

void	init_game(t_game *game)
{
	game->tex.north = NULL;
	game->tex.south = NULL;
	game->tex.west = NULL;
	game->tex.east = NULL;
	game->tex.floor[0] = -1;
	game->tex.floor[1] = -1;
	game->tex.floor[2] = -1;
	game->tex.ceiling[0] = -1;
	game->tex.ceiling[1] = -1;
	game->tex.ceiling[2] = -1;
	game->map.grid = NULL;
	game->map.height = 0;
	game->map.spawn = '\0';
	game->mlx = NULL;
	game->win = NULL;
	init_player(&game->player);
	init_img(&game->screen);
	init_img(&game->tex.no);
	init_img(&game->tex.so);
	init_img(&game->tex.we);
	init_img(&game->tex.ea);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_error("Usage: ./cub3d <file.cub>");
	init_game(&game);
	check_arg(argv[1], &game);
	init_mlx(&game);
	load_textures(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
	return (0);
}
