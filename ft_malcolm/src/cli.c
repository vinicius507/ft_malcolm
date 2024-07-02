/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:08:05 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/07/02 20:32:36 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <argp.h>
#include <libft.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <net/ethernet.h>

static int	parse_positional(int key, char *arg, struct argp_state *state)
{
	t_poison	*poison;

	poison = state->input;
	if (key == ARGP_KEY_END)
	{
		if ((poison->gratuitous && state->arg_num < 1)
			|| (!poison->gratuitous && state->arg_num < 3))
			argp_failure(state, EXIT_FAILURE, 0, "Missing required arguments");
		return (0);
	}
	if ((poison->gratuitous && state->arg_num > 1)
		|| (!poison->gratuitous && state->arg_num > 3))
		argp_failure(state, EXIT_FAILURE, 0, "Too many arguments");
	if (state->arg_num == 0)
		return (parse_ip_addr(arg, &poison->source.ip));
	if (state->arg_num == 1)
		return (parse_mac_addr(arg, poison->source.mac));
	if (state->arg_num == 2)
		return (parse_ip_addr(arg, &poison->target.ip));
	if (state->arg_num == 3)
		return (parse_mac_addr(arg, poison->target.mac));
	return (ARGP_ERR_UNKNOWN);
}

static int	parse_option(int key, char *arg, struct argp_state *state)
{
	t_poison	*poison;

	poison = state->input;
	if (key == 'g')
	{
		poison->gratuitous = true;
		ft_memset(poison->target.mac, 0xFF, ETHER_ADDR_LEN);
		return (0);
	}
	if (key == 'i')
	{
		ft_strlcpy(poison->iface.name, arg, IFNAMSIZ);
		poison->iface.index = if_nametoindex(poison->iface.name);
		if (!poison->iface.index)
			argp_failure(state, EXIT_FAILURE, 0, "Invalid interface: %s", arg);
		return (0);
	}
	if (key == 'v')
	{
		poison->verbose = true;
		return (0);
	}
	return (ARGP_ERR_UNKNOWN);
}

static int	parse_argument(int key, char *arg, struct argp_state *state)
{
	if (key == ARGP_KEY_ARG || key == ARGP_KEY_END)
		return (parse_positional(key, arg, state));
	return (parse_option(key, arg, state));
}

int	parse_arguments(t_poison *poison, int argc, char **argv)
{
	const struct argp	args = {
		.args_doc = "SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC",
		.doc = "ARP Poisoning tool built for École 42 written by vgoncalv",
		.parser = parse_argument,
		.options = (struct argp_option[]){
			{ .doc = "Positional Arguments:" },
			{ .name = "SOURCE_IP", .doc = "IP address to be spoofed as the source", .flags = OPTION_DOC },
			{ .name = "SOURCE_MAC", .doc = "MAC address to be spoofed as the source", .flags = OPTION_DOC },
			{ .name = "TARGET_IP", .doc = "IP address of the target host", .flags = OPTION_DOC },
			{ .name = "TARGET_MAC", .doc = "MAC address of the target host", .flags = OPTION_DOC },
			{ .doc = "Optional Arguments:" },
			{ .name = "gratuitous", .key = 'g', .doc = "Send a gratuitous ARP broadcast" },
			{ .name = "interface", .key = 'i', .arg = "NAME", .doc = "Network interface to use" },
			{ .name = "verbose", .key = 'v', .doc = "Enables verbose output for packet information" },
			{0},
		},
	};

	if (argp_parse(&args, argc, argv, 0, 0, poison) != 0)
		return (1);
	if (poison->gratuitous)
		poison->target.ip = poison->source.ip;
	return (0);
}
