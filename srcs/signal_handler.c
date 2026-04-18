/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loda-sil <loda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 23:45:00 by loda-sil          #+#    #+#             */
/*   Updated: 2026/04/17 20:36:27 by loda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <signal.h>

static volatile sig_atomic_t	g_sigint;

static void	handle_sigint(int sig)
{
	(void)sig;
	g_sigint = 1;
}

void	setup_signal_handlers(void)
{
	signal(SIGINT, handle_sigint);
}

int	should_close_game(void)
{
	return (g_sigint != 0);
}
