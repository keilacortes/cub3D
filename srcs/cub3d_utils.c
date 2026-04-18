/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:20:16 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/04/17 19:54:03 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(char *message)
{
	ft_printf(STDERR_FILENO, "Error\n%s\n", message);
	exit(1);
}

void	exit_error_game(t_game *game, char *message)
{
	ft_printf(STDERR_FILENO, "Error\n%s\n", message);
	if (game)
		cleanup_game(game);
	exit(1);
}

void	check_arg(char *arg, t_game *game)
{
	size_t	len;

	len = ft_strlen(arg);
	if (len < 4 || ft_strncmp(arg + len - 4, ".cub", 4) != 0)
		exit_error("Incorrect file extension, please use a <.cub> file");
	parse_file(arg, game);
}

void	free_grid(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}
