/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:01:28 by kqueiroz          #+#    #+#             */
/*   Updated: 2025/07/30 15:08:41 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	len1;
	size_t	len2;
	size_t	i;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (s1 == 0 && s2 == 0)
		return (0);
	dst = malloc((len1 + len2 + 1) * sizeof(char));
	if (dst == 0)
		return (0);
	i = -1;
	while (++i < len1)
		dst[i] = s1[i];
	i = -1;
	while (++i < len2)
		dst[i + len1] = s2[i];
	dst[len1 + len2] = '\0';
	return (dst);
}
