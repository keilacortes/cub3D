/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kqueiroz <kqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 13:56:57 by kqueiroz          #+#    #+#             */
/*   Updated: 2026/02/08 01:14:17 by kqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdint.h>
# include <stdarg.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	pf_putchar_fd(char c, int fd);
int	pf_putstr_fd(char *s, int fd);
int	pf_putnbr_fd(int n, int fd);
int	pf_putunsigned_fd(unsigned int n, int fd);
int	pf_puthex_fd(unsigned int n, char format, int fd);
int	pf_putptr_fd(void *ptr, int fd);

#endif