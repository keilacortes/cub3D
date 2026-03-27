/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 14:33:05 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/03/27 14:42:08 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*get_value(char *line)
{
	int		i;
	char	*trimmed;

	i = 0;
	while (line[i] == ' ')
		i++;
	trimmed = ft_strtrim(line + i, "\n");
	return (trimmed);
}

int	is_valid_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (!str[i])
		return (0);
	while (str[i] && str[i] != '\n')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
