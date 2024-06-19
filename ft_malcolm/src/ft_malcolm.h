/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malcolm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 19:40:17 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/19 17:06:03 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include <stdint.h>

typedef uint32_t	t_ip;
typedef uint8_t		t_mac[6];

typedef struct s_host
{
	t_ip	ip;
	t_mac	mac[6];
}	t_host;

#endif // !FT_MALCOLM_H
