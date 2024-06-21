/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:40:17 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/21 19:18:25 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <net/if.h>
# include <stdint.h>

# define BASE16 "0123456789ABCDEF"
# define MAC_SEPARATOR ':'

typedef uint32_t	t_ip;
typedef uint8_t		t_mac[6];

typedef struct s_host
{
	t_ip	ip;
	t_mac	mac;
}	t_host;

typedef struct s_cli
{
	t_host	source;
	t_host	target;
}	t_cli;

typedef struct s_poison
{
	int		sock_fd;
	char	ifname[IFNAMSIZ];
	t_host	source;
	t_host	target;
}	t_poison;

void		error(const char *fmt, ...);

int			parse_arguments(t_cli *cli, int argc, char **argv);

int			find_interface(char *ifname);

t_poison	*poison_create(t_host source, t_host target);

void		poison_destroy(t_poison *poison);

int			poison_init(t_poison *poison);

#endif // !FT_MALCOLM_H
