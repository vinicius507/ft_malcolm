/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:14:01 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/27 18:15:36 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <arpa/inet.h>
#include <errno.h>
#include <libft.h>
#include <string.h>

int	parse_ip_addr(const char *addr, t_ip *dest)
{
	int	result;

	if (addr == NULL || dest == NULL)
		return (1);
	result = inet_pton(AF_INET, addr, dest);
	if (result == 1)
		return (0);
	if (result == 0)
		error("Invalid IPv4 address");
	else
		error("Invalid IPv4 address: %s", strerror(errno));
	return (1);
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

int	parse_mac_addr(const char *addr, t_mac dest)
{
	int		idx;
	int		byte;
	char	*sanitized_mac;

	if (!is_valid_mac_addr(addr))
	{
		error("Invalid MAC address: %s", addr);
		return (1);
	}
	idx = 0;
	byte = 0;
	sanitized_mac = ft_striter(addr, ft_toupper);
	if (sanitized_mac == NULL)
	{
		error("Failed to parse MAC address");
		return (1);
	}
	while (idx < 17)
	{
		dest[byte] = ft_atoi_base(&sanitized_mac[idx], BASE16);
		byte++;
		idx += 3;
	}
	free(sanitized_mac);
	return (0);
}
