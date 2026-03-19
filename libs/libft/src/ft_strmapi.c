/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 19:13:18 by kqueiroz          #+#    #+#             */
/*   Updated: 2025/07/31 21:43:40 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;

	new_str = ft_strdup(s);
	if (new_str == 0)
		return (0);
	i = 0;
	while (new_str[i])
	{
		new_str[i] = (*f)(i, new_str[i]);
		i++;
	}
	return (new_str);
}
