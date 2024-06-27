/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:22:39 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/27 17:31:30 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	g_received_signal = 0;

static void	usage(const char *cmd)
{
	dprintf(STDERR_FILENO,
		"Usage: %s SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC\n", cmd);
}

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

int	main(int argc, char **argv)
{
	int			res;
	t_cli		cli;
	t_poison	*poison;

	ft_bzero(&cli, sizeof(t_cli));
	if (parse_arguments(&cli, argc, argv) != 0)
	{
		usage(argv[0]);
		return (EXIT_FAILURE);
	}
	register_signals();
	poison = poison_create(cli.source, cli.target);
	if (poison_bind_interface(poison) != 0 || poison_listen(poison) != 0)
	{
		poison_destroy(poison);
		if (g_received_signal != 0)
			return (g_received_signal + 128);
		return (EXIT_FAILURE);
	}
	res = poison_attack(poison);
	poison_destroy(poison);
	return (res);
}
