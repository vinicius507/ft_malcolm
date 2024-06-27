/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:22:39 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/27 19:37:20 by vgoncalv         ###   ########.fr       */
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
	g_received_signal = sig;
}

static void	register_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	signal(SIGTERM, signal_handler);
}

static int	run_poison(t_poison *poison)
{
	int	res;

	res = 0;
	if (poison->iface.name[0] != '\0')
	{
		poison->iface.index = if_nametoindex(poison->iface.name);
		if (poison->iface.index == 0)
		{
			error("Invalid network interface: %s", poison->iface.name);
			return (EXIT_FAILURE);
		}
	}
	else if (find_interface(&poison->iface) != 0)
		return (EXIT_FAILURE);
	printf("Using network interface: %s\n", poison->iface.name);
	if (poison_bind_interface(poison) != 0)
		return (EXIT_FAILURE);
	if (!poison->gratuitous && poison_listen(poison) != 0)
	{
		if (g_received_signal != 0)
			return (g_received_signal + 128);
		return (EXIT_FAILURE);
	}
	res = poison_attack(poison);
	return (res);
}

int	main(int argc, char **argv)
{
	t_poison	*poison;
	int			exit_code;

	poison = poison_create();
	if (poison == NULL)
		return (EXIT_FAILURE);
	if (parse_arguments(poison, argc, argv) != 0)
	{
		usage(argv[0]);
		poison_destroy(poison);
		return (EXIT_FAILURE);
	}
	register_signals();
	exit_code = run_poison(poison);
	poison_destroy(poison);
	return (exit_code);
}
