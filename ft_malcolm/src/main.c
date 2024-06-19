/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:22:39 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/19 18:29:37 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>

static void	usage(const char *cmd)
{
	dprintf(STDERR_FILENO,
		"Usage: %s SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC\n", cmd);
}

int	main(int argc, char **argv)
{
	t_host	source;
	t_host	target;

	if (parse_arguments(argc, argv, &source, &target) != 0)
	{
		usage(argv[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
