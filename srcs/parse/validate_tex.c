/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:09:11 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/01 14:11:11 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_file_tex(t_textures *tex)
{
	int	fd;

	fd = open(tex->north, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open north texture file");
	close(fd);
	fd = open(tex->south, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open south texture file");
	close(fd);
	fd = open(tex->west, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open west texture file");
	close(fd);
	fd = open(tex->east, O_RDONLY);
	if (fd < 0)
		exit_error("Could not open east texture file");
	close(fd);
}
