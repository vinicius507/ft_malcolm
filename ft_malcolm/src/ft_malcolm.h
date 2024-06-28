/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:40:17 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/28 11:02:57 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <net/if.h>
# include <stdbool.h>
# include <stdint.h>

# define BASE16 "0123456789ABCDEF"
# define MAC_SEPARATOR ':'
# define INET_ADDRLEN 4

extern int	g_received_signal;

typedef uint32_t	t_ip;
typedef uint8_t		t_mac[6];

typedef struct s_host
{
	t_ip	ip;
	t_mac	mac;
}	t_host;

typedef struct s_iface
{
	int		index;
	int		sock_fd;
	char	name[IFNAMSIZ];
}	t_iface;

typedef struct s_poison
{
	t_iface	iface;
	t_host	source;
	t_host	target;
	bool	verbose;
	bool	show_help;
	bool	gratuitous;
}	t_poison;

void		usage(const char *cmd);

void		error(const char *fmt, ...);

int			parse_ip_addr(const char *addr, t_ip *dest);

void		ip_to_str(t_ip ip, char *dest);

int			parse_mac_addr(const char *addr, t_mac dest);

int			parse_arguments(t_poison *poison, int argc, char **argv);

int			find_interface(t_iface *iface);

t_poison	*poison_create(void);

void		poison_destroy(t_poison *poison);

int			poison_bind_interface(t_poison *poison);

int			poison_listen(t_poison *poison);

int			poison_attack(t_poison *poison);

typedef struct s_arp
{
	t_mac		eth_dst;
	t_mac		eth_src;
	uint16_t	eth_type;
	uint16_t	ar_hrd;
	uint16_t	ar_pro;
	uint8_t		ar_hln;
	uint8_t		ar_pln;
	uint16_t	ar_op;
	t_mac		ar_sha;
	t_ip		ar_spa;
	t_mac		ar_tha;
	t_ip		ar_tpa;
} __attribute__((packed))	t_arp_packet;

int				is_arp_request(t_arp_packet packet);

void			print_arp_packet(t_arp_packet packet);

t_arp_packet	create_arp_reply(t_host *source, t_host *target);

t_arp_packet	create_gratuitous_arp_broadcast(t_host *source);

#endif // !FT_MALCOLM_H
