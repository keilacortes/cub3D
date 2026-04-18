/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:33:05 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 19:54:16 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_value(char *line)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (line[i] == ' ')
		i++;
	trimmed = ft_strtrim(line + i, "\n");
	return (trimmed);
}

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

static int	parse_values(char **values, int *rgb)
{
	int		i;

	i = 0;
	while (values[i])
		i++;
	if (i != 3)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (!is_valid_num(values[i]))
			return (0);
		rgb[i] = ft_atoi(values[i]);
		i++;
	}
	return (1);
}

int	parse_color(char *str, int *rgb)
{
	char	**values;
	int		i;
	int		commas;

	i = 0;
	commas = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ',')
			commas++;
		i++;
	}
	if (commas != 2)
		return (0);
	values = ft_split(str, ',');
	if (!values)
		return (-1);
	if (!parse_values(values, rgb))
	{
		free_grid(values);
		return (0);
	}
	free_grid(values);
	return (1);
}

int	parse_element_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (set_texture(&game->tex.north, line + 3));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (set_texture(&game->tex.south, line + 3));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (set_texture(&game->tex.west, line + 3));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (set_texture(&game->tex.east, line + 3));
	if (ft_strncmp(line, "F ", 2) == 0 && game->tex.floor[0] != -1)
		return (0);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(line + 2, game->tex.floor));
	if (ft_strncmp(line, "C ", 2) == 0 && game->tex.ceiling[0] != -1)
		return (0);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(line + 2, game->tex.ceiling));
	return (is_map_or_empty_line(line));
}
