/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/29 09:09:11 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 19:03:58 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	safe_free(char **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

static void	free_tex_paths(t_textures *tex)
{
	safe_free(&tex->north);
	safe_free(&tex->south);
	safe_free(&tex->west);
	safe_free(&tex->east);
}

static void	check_path(char *path, t_textures *tex, char *msg)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free_tex_paths(tex);
		exit_error(msg);
	}
	close(fd);
}

void	check_file_tex(t_textures *tex)
{
	check_path(tex->north, tex, "Could not open north texture file");
	check_path(tex->south, tex, "Could not open south texture file");
	check_path(tex->west, tex, "Could not open west texture file");
	check_path(tex->east, tex, "Could not open east texture file");
}
