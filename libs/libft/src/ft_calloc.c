/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:34:15 by kqueiroz          #+#    #+#             */
/*   Updated: 2025/08/07 17:17:49 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	value;
	char	*ptr;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (size > (size_t)(-1) / nmemb)
		return (0);
	value = nmemb * size;
	ptr = malloc(value);
	if (ptr == 0)
		return (0);
	ft_bzero(ptr, value);
	return (ptr);
}
