/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:10:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/17 20:05:33 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_texture(char **slot, char *line)
{
	if (*slot)
		return (0);
	*slot = get_value(line);
	if (!*slot)
		return (-1);
	return (1);
}
