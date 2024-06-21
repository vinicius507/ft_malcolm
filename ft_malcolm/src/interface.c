/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interface.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:30:49 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/21 17:36:40 by vgoncalv         ###   ########.fr       */
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

char	*find_interface(void)
{
	char			*ifname;
	struct ifaddrs	*it;
	struct ifaddrs	*addrs;

	if (getifaddrs(&addrs) == -1)
	{
		error("Failed to get network interfaces: %s", strerror(errno));
		return (NULL);
	}
	it = addrs;
	ifname = NULL;
	while (it != NULL)
	{
		if (is_eth_interface(it) != 0)
		{
			ifname = ft_strdup(it->ifa_name);
			break;
		}
		it = it->ifa_next;
	}
	freeifaddrs(addrs);
	if (ifname == NULL)
		error("No valid network interface was found");
	return (ifname);
}
