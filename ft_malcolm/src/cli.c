/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:08:05 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/07/02 17:46:43 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <stdio.h>
#include <unistd.h>
#include <net/ethernet.h>

void	usage(const char *cmd)
{
	dprintf(STDERR_FILENO,
		"Usage: %s [OPTION...] SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC\n\n"
		"ARP spoofing tool built for École 42.\n\n"
		"Positional arguments:\n"
		"  SOURCE_IP              Source IP address\n"
		"  SOURCE_MAC             Source MAC address\n"
		"  TARGET_IP              Target IP address\n"
		"  TARGET_MAC             Target MAC address\n\n"
		"Optional arguments:\n"
		"  -g, --gratuitous       Send a gratuitous ARP broadcast\n"
		"  -h, --help             Show this help message and exit\n"
		"  -i, --interface        Network interface to use\n"
		"  -v, --verbose          Verbose mode\n", cmd);
}

static int	parse_positional(t_poison *poison, char *arg)
{
	static int	idx;

	idx = idx + 1;
	if (idx == 1)
		return (parse_ip_addr(arg, &poison->source.ip));
	if (idx == 2)
		return (parse_mac_addr(arg, poison->source.mac));
	if (idx == 3)
		return (parse_ip_addr(arg, &poison->target.ip));
	if (idx == 4)
		return (parse_mac_addr(arg, poison->target.mac));
	error("Invalid argument: %s", arg);
	return (1);
}

static int	parse_option(t_poison *poison, int *idx, char **argv)
{
	if (ft_strcmp(argv[*idx], "-i") == 0 || ft_strcmp(argv[*idx], "--interface") == 0)
	{
		*idx += 1;
		if (argv[*idx] == NULL)
			return (error("Missing value for argv[*idx]: %s", argv[*idx]), 1);
		poison->iface.index = if_nametoindex(argv[*idx]);
		if (poison->iface.index == 0)
			return (error("Invalid network interface: %s", argv[*idx]), 1);
		ft_strlcpy(poison->iface.name, argv[*idx], IFNAMSIZ);
		return (0);
	}
	if (ft_strcmp(argv[*idx], "-g") == 0 || ft_strcmp(argv[*idx], "--gratuitous") == 0)
	{
		poison->gratuitous = true;
		poison->target.ip = poison->source.ip;
		ft_memset(poison->target.mac, 0xFF, ETHER_ADDR_LEN);
		return (0);
	}
	if (ft_strcmp(argv[*idx], "-v") == 0 || ft_strcmp(argv[*idx], "--verbose") == 0)
	{
		poison->verbose = 1;
		return (0);
	}
	return (error("Invalid argv[*idx]: %s", argv[*idx]), 1);
}

static bool	has_help_option(int argc, char **argv)
{
	int	idx;

	idx = 0;
	while (++idx < argc)
	{
		if (ft_strcmp(argv[idx], "-h") == 0
			|| ft_strcmp(argv[idx], "--help") == 0)
			return (true);
	}
	return (false);
}

int	parse_arguments(t_poison *poison, int argc, char **argv)
{
	int		idx;
	bool	is_option;

	if (has_help_option(argc, argv))
	{
		usage(argv[0]);
		exit(EXIT_SUCCESS);
	}
	if (argc < 5)
	{
		error("Missing required arguments");
		return (1);
	}
	idx = 0;
	while (++idx < argc)
	{
		is_option = argv[idx][0] == '-';
		if (is_option && parse_option(poison, &idx, argv) != 0)
			return (1);
		if (!is_option && parse_positional(poison, argv[idx]) != 0)
			return (1);
	}
	return (0);
}
