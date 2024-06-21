/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:30:49 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/21 19:18:11 by vgoncalv         ###   ########.fr       */
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

int	find_interface(char *ifname)
{
	int				ret;
	struct ifaddrs	*it;
	struct ifaddrs	*addrs;

	if (getifaddrs(&addrs) == -1)
	{
		error("Failed to get network interfaces: %s", strerror(errno));
		return (1);
	}
	ret = 1;
	it = addrs;
	while (it != NULL)
	{
		if (is_eth_interface(it) != 0)
		{
			ret = 0;
			ft_strlcpy(ifname, it->ifa_name, IFNAMSIZ);
			break;
		}
		it = it->ifa_next;
	}
	freeifaddrs(addrs);
	if (ret == 1)
		error("No valid network interface was found");
	return (ret);
}
