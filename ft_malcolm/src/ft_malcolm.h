/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:40:17 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/19 18:07:45 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

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

int	parse_arguments(int argc, char **argv, t_host *source, t_host *target);

#endif // !FT_MALCOLM_H
