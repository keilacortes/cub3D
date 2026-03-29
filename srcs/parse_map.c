/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:11:42 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/03/29 12:03:20 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	file_count(const char *file)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open file");
	line = get_next_line(fd);
	lines = 0;
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
		lines++;
	}
	close(fd);
	return (lines);
}

static char	**copy_file(const char *file)
{
	char	**grid;
	char	*line;
	int		lines;
	int		fd;
	int		i;

	lines = file_count(file);
	grid = malloc(sizeof(char *) * (lines + 1));
	if (!grid)
		exit_error("Malloc failed");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open file");
	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		grid[i++] = ft_strtrim(line, "\n");
		free(line);
		line = get_next_line(fd);
	}
	grid[i] = NULL;
	close(fd);
	return (grid);
}

static int	map_count(char **file_grid, int lines, t_map *map)
{
	int	i;

	i = lines - 1;
	while (i >= 0 && file_grid[i][0] == '\0')
		i--;
	while (i >= 0 && file_grid[i][0] != '\0')
	{
		map->height++;
		i--;
	}
	return (i + 1);
}

static void	copy_map(char **file_grid, int lines, t_map *map)
{
	int	start;
	int	i;

	start = map_count(file_grid, lines, map);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		exit_error("Malloc failed");
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(file_grid[start + i]);
		i++;
	}
	map->grid[i] = NULL;
}

void	parse_map(const char *file, t_map *map)
{
	char	**file_grid;
	int		lines;

	file_grid = copy_file(file);
	lines = 0;
	while (file_grid[lines])
		lines++;
	copy_map(file_grid, lines, map);
	free_grid(file_grid);
}
