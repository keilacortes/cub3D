/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 12:37:56 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 20:16:51 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_tile(t_game *game, int pos[2])
{
	t_map		*map;
	t_player	*player;
	char		c;

	map = &game->map;
	player = &game->player;
	c = map->grid[pos[0]][pos[1]];
	if (c == '1' || c == '0' || c == ' ')
		return ;
	if (!player_pos(player, c, pos[0], pos[1]))
	{
		free_grid(map->grid);
		map->grid = NULL;
		exit_error_game(game, "Map has invalid characters");
	}
	map->spawn = c;
	map->grid[pos[0]][pos[1]] = '0';
}

static void	validate_char(t_game *game)
{
	t_map		*map;
	t_player	*player;
	int			pos[2];

	map = &game->map;
	player = &game->player;
	pos[0] = 0;
	while (map->grid[pos[0]] != NULL)
	{
		pos[1] = 0;
		while (map->grid[pos[0]][pos[1]])
		{
			validate_tile(game, pos);
			pos[1]++;
		}
		pos[0]++;
	}
	if (!player->spawn_found)
	{
		free_grid(map->grid);
		map->grid = NULL;
		exit_error_game(game, "Map has no spawn point");
	}
}

static int	check_neighbors(char **grid, int x, int y, int height)
{
	int	width;
	int	up_width;
	int	down_width;

	width = ft_strlen(grid[x]);
	if (x - 1 < 0 || x + 1 >= height)
		return (1);
	if (y - 1 < 0 || y + 1 >= width)
		return (1);
	up_width = ft_strlen(grid[x - 1]);
	down_width = ft_strlen(grid[x + 1]);
	if (y >= up_width || y >= down_width)
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

static int	validate_path(char **grid, int height, char spawn)
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

void	validate_map(t_game *game)
{
	validate_char(game);
	if (validate_path(game->map.grid, game->map.height, game->map.spawn))
	{
		free_grid(game->map.grid);
		game->map.grid = NULL;
		exit_error_game(game, "Map is not closed");
	}
}
