/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_putunsigned_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 20:28:44 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/08 01:19:47 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pf_putunsigned_fd(unsigned int n, int fd)
{
	int	count;

	if (fd < 0)
		return (0);
	count = 0;
	if (n >= 10)
		count += pf_putunsigned_fd(n / 10, fd);
	count += pf_putchar_fd((n % 10) + '0', fd);
	return (count);
}
