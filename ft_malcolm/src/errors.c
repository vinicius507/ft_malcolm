/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:43:55 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/19 18:46:31 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <stdio.h>
#include <unistd.h>

void	invalid_ip_addr(const char *ip_addr)
{
	dprintf(STDERR_FILENO, "Error: invalid IPv4 address: %s\n", ip_addr);
}

void	invalid_mac_addr(const char *mac_addr)
{
	dprintf(STDERR_FILENO, "Error: invalid mac address: %s\n", mac_addr);
}
