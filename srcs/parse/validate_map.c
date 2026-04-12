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

int	player_pos(t_player *player, char c, int x, int y)
{
	if (player->spawn_found)
		return (0);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		player->pos_x = y;
		player->pos_y = x;
		player->spawn_found = 1;
		if (c == 'N')
		{
			player->dir_x = 0;
			player->dir_y = -1;
			player->plane_x = 0.66;
			player->plane_y = 0;
		}
		else if (c == 'S')
		{
			player->dir_x = 0;
			player->dir_y = 1;
			player->plane_x = -0.66;
			player->plane_y = 0;
		}
		else if (c == 'E')
		{
			player->dir_x = 1;
			player->dir_y = 0;
			player->plane_x = 0;
			player->plane_y = 0.66;
		}
		else if (c == 'W')
		{
			player->dir_x = -1;
			player->dir_y = 0;
			player->plane_x = 0;
			player->plane_y = -0.66;
		}
		return (1);
	}
	return (0);
}

void	validate_char(char **grid, t_player *player, t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (grid[i] != NULL)
	{
		j = 0;
		while (grid[i][j])
		{
			if (grid[i][j] != '1' && grid[i][j] != '0' && grid[i][j] != ' ')
			{
				if (player_pos(player, grid[i][j], i, j))
				{
					map->spawn = grid[i][j];
					grid[i][j] = '0';
				}
				else
				{
					free_grid(grid);
					exit_error("Map has invalid characters");
				}
			}
			j++;
		}
		i++;
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
