/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_spawn.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loena <loena@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:48:37 by loena             #+#    #+#             */
/*   Updated: 2026/04/17 15:59:35 by loena            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_ns_dir(t_player *player, char c)
{
	player->dir_x = 0;
	if (c == 'N')
	{
		player->dir_y = -1;
		player->plane_x = 0.66;
	}
	else
	{
		player->dir_y = 1;
		player->plane_x = -0.66;
	}
	player->plane_y = 0;
}

static void	set_ew_dir(t_player *player, char c)
{
	player->dir_y = 0;
	if (c == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	else
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
	}
	player->plane_x = 0;
}

static void	set_player_dir(t_player *player, char c)
{
	if (c == 'N' || c == 'S')
		set_ns_dir(player, c);
	else
		set_ew_dir(player, c);
}

int	player_pos(t_player *player, char c, int x, int y)
{
	if (player->spawn_found)
		return (0);
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (0);
	player->pos_x = y;
	player->pos_y = x;
	player->spawn_found = 1;
	set_player_dir(player, c);
	return (1);
}
