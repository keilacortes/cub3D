/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:20:16 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/03/25 14:09:05 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message)
{
	ft_printf(STDERR_FILENO, "Error\n%s\n", message);
	exit(1);
}

void	check_arg(char *arg)
{
	if (!ft_strnstr(arg, ".cub", ft_strlen(arg)))
		exit_error("Incorrect file extension, please use a <.cub> file");
}
