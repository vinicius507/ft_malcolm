/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poison.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:21:24 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/25 18:56:35 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <errno.h>
#include <libft.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

t_poison	*poison_create(t_host source, t_host target)
{
	t_poison	*poison;

	poison = ft_calloc(1, sizeof(t_poison));
	poison->source = source;
	poison->target = target;
	return (poison);
}

void	poison_destroy(t_poison *poison)
{
	if (poison->sock_fd > 0)
		close(poison->sock_fd);
	free(poison);
}

int	poison_bind_interface(t_poison *poison)
{
	struct ifreq	req;

	if (find_interface(poison->ifname) != 0)
		return (1);
	printf("Found interface: %s\n", poison->ifname);
	poison->sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (poison->sock_fd == -1)
	{
		error("Failed to open socket: %s", strerror(errno));
		return (1);
	}
	printf("Opened socket: %d\n", poison->sock_fd);
	ft_bzero(&req, sizeof(struct ifreq));
	ft_strlcpy(req.ifr_name, poison->ifname, IFNAMSIZ);
	if (setsockopt(poison->sock_fd, SOL_SOCKET, SO_BINDTODEVICE, &req, sizeof(req)) == -1)
	{
		error("Failed to bind socket to interface: %s", strerror(errno));
		return (1);
	}
	printf("Bound socket to the %s interface\n", poison->ifname);
	return (0);
}


static int	is_poison_target(t_poison *poison, t_arp *packet)
{
	if (ft_memcmp(poison->target.mac, packet->ar_sha, 6) != 0)
		return (0);
	if (poison->target.ip != packet->ar_spa)
		return (0);
	if (poison->source.ip != packet->ar_tpa)
		return (0);
	return (1);
}

int	poison_listen(t_poison *poison)
{
	ssize_t	read;
	t_arp	packet;

	ft_bzero(&packet, sizeof(t_arp));
	printf("Listening for ARP packets\n");
	while (1)
	{
		read = recvfrom(poison->sock_fd, &packet, sizeof(t_arp), 0, NULL, NULL);
		if (read == -1)
		{
			error("Failed to read ARP packet: %s", strerror(errno));
			return (1);
		}
		if (is_arp_request(packet) && is_poison_target(poison, &packet))
		{
			printf("Received target ARP request\n");
			return (0);
		}
	}
}
