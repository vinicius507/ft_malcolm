/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:54:27 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/27 19:18:46 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <net/if_arp.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <stdio.h>

int	is_arp_request(t_arp packet)
{
	return (ntohs(packet.ar_op) == 1);
}

void	print_arp_packet(t_arp packet)
{
	char	src_ip[INET_ADDRSTRLEN];
	char	dst_ip[INET_ADDRSTRLEN];

	ip_to_str(packet.ar_spa, src_ip);
	ip_to_str(packet.ar_tpa, dst_ip);
	printf("ARP packet:\n");
	printf("  Hardware type: %d\n", ntohs(packet.ar_hrd));
	printf("  Protocol type: 0x%04x\n", ntohs(packet.ar_pro));
	printf("  Hardware address length: %d\n", packet.ar_hln);
	printf("  Protocol address length: %d\n", packet.ar_pln);
	printf("  Opcode: %d\n", ntohs(packet.ar_op));
	printf("  Sender MAC address: %s\n",
		ether_ntoa((struct ether_addr *)&packet.ar_sha));
	printf("  Sender IP address: %s\n", src_ip);
	printf("  Target MAC address: %s\n",
		ether_ntoa((struct ether_addr *)&packet.ar_tha));
	printf("  Target IP address: %s\n", dst_ip);
}

t_arp	create_arp_reply(t_host *source, t_host *target)
{
	t_arp	packet;

	ft_bzero(&packet, sizeof(t_arp));
	ft_memcpy(packet.eth_dst, target->mac, ETHER_ADDR_LEN);
	ft_memcpy(packet.eth_src, source->mac, ETHER_ADDR_LEN);
	packet.eth_type = htons(ETH_P_ARP);
	packet.ar_hrd = htons(ARPHRD_ETHER);
	packet.ar_pro = htons(ETH_P_IP);
	packet.ar_hln = ETHER_ADDR_LEN;
	packet.ar_pln = INET_ADDRLEN;
	packet.ar_op = htons(ARPOP_REPLY);
	ft_memcpy(packet.ar_sha, source->mac, ETHER_ADDR_LEN);
	packet.ar_spa = source->ip;
	ft_memcpy(packet.ar_tha, target->mac, ETHER_ADDR_LEN);
	packet.ar_tpa = target->ip;
	return (packet);
}

t_arp	create_gratuitous_arp_reply(t_host *source)
{
	t_arp	packet;

	ft_bzero(&packet, sizeof(t_arp));
	ft_memset(packet.eth_dst, 0xFF, ETHER_ADDR_LEN);
	ft_memcpy(packet.eth_src, source->mac, ETHER_ADDR_LEN);
	packet.eth_type = htons(ETH_P_ARP);
	packet.ar_hrd = htons(ARPHRD_ETHER);
	packet.ar_pro = htons(ETH_P_IP);
	packet.ar_hln = ETHER_ADDR_LEN;
	packet.ar_pln = INET_ADDRLEN;
	packet.ar_op = htons(ARPOP_REPLY);
	ft_memcpy(packet.ar_sha, source->mac, ETHER_ADDR_LEN);
	packet.ar_spa = source->ip;
	ft_memset(packet.ar_tha, 0xFF, ETHER_ADDR_LEN);
	packet.ar_tpa = source->ip;
	return (packet);
}
