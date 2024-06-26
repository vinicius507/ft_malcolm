/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:30:49 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/26 07:46:51 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <errno.h>
#include <ifaddrs.h>
#include <libft.h>
#include <net/if.h>
#include <string.h>

static int	is_eth_interface(struct ifaddrs *iface)
{
	if (!(iface->ifa_flags & (IFF_UP | IFF_RUNNING)))
		return (0);
	if (iface->ifa_flags & (IFF_LOOPBACK))
		return (0);
	return (iface->ifa_addr->sa_family == AF_PACKET);
}

int	find_interface(t_iface *iface)
{
	struct ifaddrs	*it;
	struct ifaddrs	*addrs;

	if (getifaddrs(&addrs) == -1)
	{
		error("Failed to get network interfaces: %s", strerror(errno));
		return (1);
	}
	it = addrs;
	while (it != NULL)
	{
		if (is_eth_interface(it) != 0)
		{
			ft_strlcpy(iface->name, it->ifa_name, IFNAMSIZ);
			iface->index = if_nametoindex(iface->name);
			break;
		}
		it = it->ifa_next;
	}
	freeifaddrs(addrs);
	if (iface->index == 0)
	{
		error("No valid network interface was found");
		return (1);
	}
	return (0);
}
