/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:47:18 by kqueiroz          #+#    #+#             */
/*   Updated: 2025/07/29 15:47:22 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	sub_len;

	if (s == 0)
		return (0);
	sub_len = ft_strlen(s);
	if (start >= sub_len)
		return (ft_strdup(""));
	if (start + len > sub_len)
		len = sub_len - start;
	sub_str = malloc((len + 1) * sizeof(char));
	if (sub_str == 0)
		return (0);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
}
