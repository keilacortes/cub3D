/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 15:10:44 by kqueiroz          #+#    #+#             */
/*   Updated: 2025/08/05 19:42:39 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		len_s;
	int		len_d;
	char	*dst;

	i = 0;
	while (s1[i] && ft_in_set(s1[i], set))
		i++;
	len_s = ft_strlen(s1) - 1;
	while (len_s >= i && ft_in_set(s1[len_s], set))
		len_s--;
	len_d = len_s - i + 1;
	dst = malloc((len_d + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	j = -1;
	while (++j < len_d)
	{
		dst[j] = s1[i];
		i++;
	}
	dst[j] = '\0';
	return (dst);
}
