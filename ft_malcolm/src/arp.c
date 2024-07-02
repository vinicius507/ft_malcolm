/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:54:27 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/07/02 17:51:29 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <errno.h>
#include <libft.h>
#include <linux/if_packet.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

int	is_arp_request(t_arp_packet *packet)
{
	return (ntohs(packet->ar_op) == ARPOP_REQUEST);
}

void	print_arp_packet(t_arp_packet *packet)
{
	char	src_ip[INET_ADDRSTRLEN];
	char	dst_ip[INET_ADDRSTRLEN];

	ip_to_str(packet->ar_spa, src_ip);
	ip_to_str(packet->ar_tpa, dst_ip);
	printf("ARP packet:\n");
	printf("  Hardware type: %d\n", ntohs(packet->ar_hrd));
	printf("  Protocol type: 0x%04x\n", ntohs(packet->ar_pro));
	printf("  Hardware address length: %d\n", packet->ar_hln);
	printf("  Protocol address length: %d\n", packet->ar_pln);
	printf("  Opcode: %d\n", ntohs(packet->ar_op));
	printf("  Sender MAC address: %s\n",
		ether_ntoa((struct ether_addr *)&packet->ar_sha));
	printf("  Sender IP address: %s\n", src_ip);
	printf("  Target MAC address: %s\n",
		ether_ntoa((struct ether_addr *)&packet->ar_tha));
	printf("  Target IP address: %s\n", dst_ip);
}

t_arp_packet	create_arp_packet(int op, t_host *source, t_host *target)
{
	t_arp_packet	packet;

	ft_bzero(&packet, sizeof(t_arp_packet));
	ft_memcpy(packet.eth_dst, target->mac, ETHER_ADDR_LEN);
	ft_memcpy(packet.eth_src, source->mac, ETHER_ADDR_LEN);
	packet.eth_type = htons(ETH_P_ARP);
	packet.ar_hrd = htons(ARPHRD_ETHER);
	packet.ar_pro = htons(ETH_P_IP);
	packet.ar_hln = ETHER_ADDR_LEN;
	packet.ar_pln = INET_ADDRLEN;
	packet.ar_op = htons(op);
	ft_memcpy(packet.ar_sha, source->mac, ETHER_ADDR_LEN);
	packet.ar_spa = source->ip;
	ft_memcpy(packet.ar_tha, target->mac, ETHER_ADDR_LEN);
	packet.ar_tpa = target->ip;
	return (packet);
}

int	send_arp_packet(t_poison *poison, t_arp_packet *packet)
{
	ssize_t				sent_bytes;
	struct sockaddr_ll	sockaddr;

	sockaddr = (struct sockaddr_ll){
		.sll_family = AF_PACKET,
		.sll_halen = ETHER_ADDR_LEN,
		.sll_ifindex = poison->iface.index,
		.sll_protocol = htons(ETH_P_ARP),
	};
	ft_memcpy(sockaddr.sll_addr, poison->target.mac, ETHER_ADDR_LEN);
	sent_bytes = sendto(poison->iface.sock_fd, packet, sizeof(t_arp_packet), 0,
			(struct sockaddr *)&sockaddr, sizeof(struct sockaddr_ll));
	if (sent_bytes == -1)
	{
		error("Failed to send ARP packet: %s", strerror(errno));
		return (1);
	}
	printf("ARP packet sent: %zd bytes\n", sent_bytes);
	return (0);
}
