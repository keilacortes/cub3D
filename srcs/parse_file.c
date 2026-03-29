/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:37:56 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/03/29 09:14:42 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_color(char *str, int *rgb)
{
	char	**values;
	int		i;

	values = ft_split(str, ',');
	i = 0;
	while (values[i])
		i++;
	if (i != 3)
	{
		free_split(values);
		exit_error("Color must have exactly 3 values (R,G,B)");
	}
	i = 0;
	while (i < 3)
	{
		if (!is_valid_num(values[i]))
		{
			free_split(values);
			exit_error("Invalid color value");
		}
		rgb[i] = ft_atoi(values[i]);
		i++;
	}
	free_split(values);
}

static void	parse_elements(const char *file, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strncmp(line, "NO ", 3) == 0)
			game->tex.north = get_value(line + 3);
		else if (ft_strncmp(line, "SO ", 3) == 0)
			game->tex.south = get_value(line + 3);
		else if (ft_strncmp(line, "WE ", 3) == 0)
			game->tex.west = get_value(line + 3);
		else if (ft_strncmp(line, "EA ", 3) == 0)
			game->tex.east = get_value(line + 3);
		else if (ft_strncmp(line, "F ", 2) == 0)
			parse_color(line + 2, game->tex.floor);
		else if (ft_strncmp(line, "C ", 2) == 0)
			parse_color(line + 2, game->tex.ceiling);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

static void	validate_textures(t_textures *tex)
{
	if (!tex->north || !tex->south || !tex->west || !tex->east)
		exit_error("Missing texture element (NO, SO, WE or EA)");
}

static void	validate_colors(t_textures *tex)
{
	int	i;

	if (tex->floor[0] == -1)
		exit_error("Missing color element (F)");
	else if (tex->ceiling[0] == -1)
		exit_error("Missing color element (C)");
	i = 0;
	if (tex->floor[i] < 0 || tex->floor[i] > 255 || tex->ceiling[i] < 0
		|| tex->ceiling[i] > 255)
	{
		exit_error("Color value out of range [0, 255]");
	}
}

void	parse_file(const char *file, t_game *game)
{
	parse_elements(file, game);
	validate_textures(&game->tex);
	validate_colors(&game->tex);
}
