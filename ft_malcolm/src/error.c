/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 18:43:55 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/06/20 17:04:30 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malcolm.h"
#include <errno.h>
#include <libft.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

void	error(const char *fmt, ...)
{
	char	*efmt;
	va_list	args;

	va_start(args, fmt);
	if (asprintf(&efmt, "Error: %s\n", fmt) == EOF)
		return (ft_putendl_fd("Unknown Error", STDERR_FILENO));
	vdprintf(STDERR_FILENO, efmt, args);
	free(efmt);
	va_end(args);
}
