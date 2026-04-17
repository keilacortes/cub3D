/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:37:56 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/06 19:58:12 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_tile(char **grid, t_player *player, t_map *map, int pos[2])
{
	char	c;

	c = grid[pos[0]][pos[1]];
	if (c == '1' || c == '0' || c == ' ')
		return ;
	if (!player_pos(player, c, pos[0], pos[1]))
	{
		free_grid(grid);
		exit_error("Map has invalid characters");
	}
	map->spawn = c;
	grid[pos[0]][pos[1]] = '0';
}

void	validate_char(char **grid, t_player *player, t_map *map)
{
	int	pos[2];

	pos[0] = 0;
	while (grid[pos[0]] != NULL)
	{
		pos[1] = 0;
		while (grid[pos[0]][pos[1]])
		{
			validate_tile(grid, player, map, pos);
			pos[1]++;
		}
		pos[0]++;
	}
	if (!player->spawn_found)
		exit_error("Map has no spawn point");
}

int	check_neighbors(char **grid, int x, int y, int height)
{
	int	width;

	width = ft_strlen(grid[x]);
	if (x - 1 < 0 || x + 1 >= height)
		return (1);
	if (y - 1 < 0 || y + 1 >= width)
		return (1);
	if (grid[x - 1][y] == ' ' || grid[x - 1][y] == '\0')
		return (1);
	if (grid[x + 1][y] == ' ' || grid[x + 1][y] == '\0')
		return (1);
	if (grid[x][y - 1] == ' ' || grid[x][y - 1] == '\0')
		return (1);
	if (grid[x][y + 1] == ' ' || grid[x][y + 1] == '\0')
		return (1);
	return (0);
}

int	validate_path(char **grid, int height, char spawn)
{
	int	x;
	int	y;

	x = 0;
	while (x < height)
	{
		y = 0;
		while (grid[x][y])
		{
			if (grid[x][y] == '0' || grid[x][y] == spawn)
			{
				if (check_neighbors(grid, x, y, height))
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}

void	validate_map(t_map *map, t_player *player)
{
	validate_char(map->grid, player, map);
	if (validate_path(map->grid, map->height, map->spawn))
	{
		free_grid(map->grid);
		exit_error("Map is not closed");
	}
}
