/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:22:39 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/07/02 18:15:28 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	g_received_signal = 0;

static void	signal_handler(int sig)
{
	static const char	*signals[] = {
		[SIGINT] = "SIGINT",
		[SIGQUIT] = "SIGQUIT",
		[SIGTERM] = "SIGTERM"
	};

	printf("\nReceived signal %s, exiting...\n", signals[sig]);
	g_received_signal = sig;
}

static void	register_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
}

int	main(int argc, char **argv)
{
	t_poison	poison;

	poison_init(&poison);
	if (parse_arguments(&poison, argc, argv) != 0)
		return (EXIT_FAILURE);
	if (getuid() != 0)
	{
		error("You must have root privileges to run this program");
		return (EXIT_FAILURE);
	}
	register_signals();
	if (poison.iface.index == 0 && find_interface(&poison.iface) != 0)
		return (EXIT_FAILURE);
	printf("Using network interface: %s\n", poison.iface.name);
	if (poison_bind_interface(&poison) != 0 || poison_attack(&poison) != 0)
	{
		poison_destroy(&poison);
		if (g_received_signal != 0)
			return (g_received_signal + 128);
		return (EXIT_FAILURE);
	}
	poison_destroy(&poison);
	return (EXIT_SUCCESS);
}
