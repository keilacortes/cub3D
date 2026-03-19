/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 15:16:28 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/08 01:18:24 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_format(char format, va_list args)
{
	int	fd;

	fd = 1;
	if (format == '%')
		return (pf_putchar_fd('%', fd));
	else if (format == 'c')
		return (pf_putchar_fd(va_arg(args, int), fd));
	else if (format == 's')
		return (pf_putstr_fd(va_arg(args, char *), fd));
	else if (format == 'p')
		return (pf_putptr_fd(va_arg(args, void *), fd));
	else if (format == 'd' || format == 'i')
		return (pf_putnbr_fd(va_arg(args, int), fd));
	else if (format == 'u')
		return (pf_putunsigned_fd(va_arg(args, unsigned int), fd));
	else if (format == 'x' || format == 'X')
		return (pf_puthex_fd(va_arg(args, unsigned int), format, fd));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		count;

	va_start(args, format);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += check_format(*format, args);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end (args);
	return (count);
}
