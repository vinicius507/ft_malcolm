/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 15:22:39 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/19 17:07:24 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <arpa/inet.h>
#include <libft.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	usage(const char *cmd)
{
	printf("Usage: %s SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC\n", cmd);
}

int	parse_ip_addr(const char *addr, t_ip *dest)
{
	int	result;

	if (addr == NULL || dest == NULL)
		return (1);
	result = inet_pton(AF_INET, addr, dest);
	if (result <= 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid IP address: %s\n", addr);
		return (1);
	}
	return (0);
}

int	parse_arguments(int argc, char **argv, t_host *source, t_host *target)
{
	if (argc != 5)
		return (1);
	if (parse_ip_addr(argv[1], &source->ip) != 0)
		return (1);
	if (parse_ip_addr(argv[3], &target->ip) != 0)
		return (1);
	return (0);
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
