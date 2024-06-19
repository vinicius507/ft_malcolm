/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 17:08:05 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/19 18:28:52 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <arpa/inet.h>
#include <libft.h>
#include <stdio.h>
#include <unistd.h>

static int	parse_ip_addr(const char *addr, t_ip *dest)
{
	int	result;

	if (addr == NULL || dest == NULL)
		return (1);
	result = inet_pton(AF_INET, addr, dest);
	if (result <= 0)
		return (1);
	return (0);
}

static int	is_valid_mac_addr(const char *addr)
{
	int	idx;

	if (ft_strlen(addr) != 17)
		return (0);
	idx = 0;
	while (addr[idx] != '\0')
	{
		if (idx % 3 == 2)
		{
			if (addr[idx] != MAC_SEPARATOR)
				return (0);
		}
		else if (ft_strchr(BASE16, ft_toupper(addr[idx])) == NULL)
			return (0);
		idx++;
	}
	return (1);
}

static int	parse_mac_addr(const char *addr, t_mac dest)
{
	int		idx;
	int		byte;
	char	*sanitized_mac;

	if (addr == NULL || dest == NULL)
		return (1);
	if (!is_valid_mac_addr(addr))
		return (1);
	idx = 0;
	byte = 0;
	sanitized_mac = ft_striter(addr, ft_toupper);
	if (sanitized_mac == NULL)
		return (1);
	while (idx < 17)
	{
		dest[byte] = ft_atoi_base(&sanitized_mac[idx], BASE16);
		byte++;
		idx += 3;
	}
	free(sanitized_mac);
	return (0);
}

int	parse_arguments(int argc, char **argv, t_host *source, t_host *target)
{
	if (argc != 5)
		return (1);
	if (parse_ip_addr(argv[1], &source->ip) != 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid ip address: %s\n", argv[1]);
		return (1);
	}
	if (parse_mac_addr(argv[2], source->mac) != 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid mac address: %s\n", argv[2]);
		return (1);
	}
	if (parse_ip_addr(argv[3], &target->ip) != 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid ip address: %s\n", argv[3]);
		return (1);
	}
	if (parse_mac_addr(argv[4], target->mac) != 0)
	{
		dprintf(STDERR_FILENO, "Error: invalid mac address: %s\n", argv[4]);
		return (1);
	}
	return (0);
}
