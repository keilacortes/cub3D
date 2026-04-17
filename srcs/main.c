/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:51:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/16 21:17:05 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	game->player.spawn_found = 0;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	game->player.keys.a = 0;
	game->player.keys.d = 0;
	game->player.keys.s = 0;
	game->player.keys.w = 0;
	game->player.keys.left = 0;
	game->player.keys.right = 0;
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		exit_error("Usage: ./cub3d <file.cub>");
	init_game(&game);
	check_arg(argv[1], &game);
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, WIDTH, HEIGHT, "cub3D");
	game.screen.img = mlx_new_image(game.mlx, WIDTH, HEIGHT);
	game.screen.addr = mlx_get_data_addr(game.screen.img, 
			&game.screen.bpp, &game.screen.line_len, &game.screen.endian);
	load_textures(&game);
	setup_hooks(&game);
	mlx_loop(game.mlx);
}
