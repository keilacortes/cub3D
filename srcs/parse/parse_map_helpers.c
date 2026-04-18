/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:00:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/17 20:03:05 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_file_fail(char **grid, int fd, int i, t_game *game)
{
	close(fd);
	grid[i] = NULL;
	free_grid(grid);
	exit_error_game(game, "Malloc failed");
}

int	open_grid_file(const char *file, char **grid, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		free(grid);
		exit_error_game(game, "Could not open file");
	}
	return (fd);
}

void	fill_grid(char **grid, int fd, t_game *game)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		grid[i] = ft_strtrim(line, "\n");
		if (!grid[i])
			copy_file_fail(grid, fd, i, game);
		free(line);
		i++;
		line = get_next_line(fd);
	}
	grid[i] = NULL;
}

int	is_map_or_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' '
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}
