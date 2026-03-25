/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 13:51:06 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/03/25 15:09:01 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*win;

	if (argc != 2)
		exit_error("Usage: ./cub3d <file.cub>");
	check_arg(argv[1]);
	mlx = mlx_init();
	win = mlx_new_window(mlx, 800, 600, "cub3D");
	(void)win;
	mlx_loop(mlx);
}
