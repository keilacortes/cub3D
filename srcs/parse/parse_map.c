/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 16:11:42 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 19:55:57 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		open_grid_file(const char *file, char **grid, t_game *game);
void	fill_grid(char **grid, int fd, t_game *game);

static int	file_count(const char *file, t_game *game)
{
	char	*line;
	int		fd;
	int		lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit_error_game(game, "Could not open file");
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

static char	**copy_file(const char *file, t_game *game)
{
	char	**grid;
	int		lines;
	int		fd;

	lines = file_count(file, game);
	grid = malloc(sizeof(char *) * (lines + 1));
	if (!grid)
		exit_error_game(game, "Malloc failed");
	fd = open_grid_file(file, grid, game);
	fill_grid(grid, fd, game);
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

static void	copy_map(char **file_grid, int lines, t_game *game)
{
	t_map	*map;
	int		start;
	int		i;

	map = &game->map;
	start = map_count(file_grid, lines, map);
	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		exit_error_game(game, "Malloc failed");
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = ft_strdup(file_grid[start + i]);
		if (!map->grid[i])
		{
			map->grid[i] = NULL;
			free_grid(map->grid);
			map->grid = NULL;
			exit_error_game(game, "Malloc failed");
		}
		i++;
	}
	map->grid[i] = NULL;
}

void	parse_map(const char *file, t_game *game)
{
	char	**file_grid;
	int		lines;

	file_grid = copy_file(file, game);
	lines = 0;
	while (file_grid[lines])
		lines++;
	copy_map(file_grid, lines, game);
	free_grid(file_grid);
	validate_map(game);
}
