/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 15:54:27 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/27 18:34:52 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <libft.h>
#include <net/if_arp.h>
#include <netinet/ether.h>
#include <netinet/in.h>

int	is_arp_request(t_arp packet)
{
	return (ntohs(packet.ar_op) == 1);
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
