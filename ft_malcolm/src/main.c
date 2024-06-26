/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:22:39 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/26 07:59:57 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	usage(const char *cmd)
{
	dprintf(STDERR_FILENO,
		"Usage: %s SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC\n", cmd);
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
	poison = poison_create(cli.source, cli.target);
	if (poison_bind_interface(poison) != 0 || poison_listen(poison) != 0)
	{
		poison_destroy(poison);
		return (EXIT_FAILURE);
	}
	res = poison_attack(poison);
	poison_destroy(poison);
	return (res);
}
