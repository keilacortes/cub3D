/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:37:56 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 23:05:00 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_tex_paths(t_textures *tex)
{
	if (tex->north)
		free(tex->north);
	if (tex->south)
		free(tex->south);
	if (tex->west)
		free(tex->west);
	if (tex->east)
		free(tex->east);
	tex->north = NULL;
	tex->south = NULL;
	tex->west = NULL;
	tex->east = NULL;
}

static void	parse_fail(t_game *game, char *msg)
{
	free_tex_paths(&game->tex);
	exit_error(msg);
}

static void	drain_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	parse_elements(const char *file, t_game *game)
{
	int		fd;
	int		status;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open file");
	line = get_next_line(fd);
	while (line)
	{
		status = parse_element_line(game, line);
		if (status <= 0)
		{
			free(line);
			drain_fd(fd);
			if (status == -1)
				parse_fail(game, "Malloc failed");
			parse_fail(game, "Duplicate texture or invalid color");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	parse_file(const char *file, t_game *game)
{
	int	i;

	parse_elements(file, game);
	if (!game->tex.north || !game->tex.south
		|| !game->tex.west || !game->tex.east)
		parse_fail(game, "Missing texture element (NO, SO, WE or EA)");
	check_file_tex(&game->tex);
	if (game->tex.floor[0] == -1 || game->tex.ceiling[0] == -1)
		parse_fail(game, "Missing color element (F or C)");
	i = 0;
	while (i < 3)
	{
		if (game->tex.floor[i] < 0 || game->tex.floor[i] > 255
			|| game->tex.ceiling[i] < 0 || game->tex.ceiling[i] > 255)
			parse_fail(game, "Color value out of range [0, 255]");
		i++;
	}
	parse_map(file, game);
}
