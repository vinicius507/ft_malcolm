/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 22:42:03 by vgoncalv          #+#    #+#             */
/*   Updated: 2024/07/02 23:42:08 by vgoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../src/ft_malcolm.h"
#include "netinet/in.h"
#include <minunit.h>

#define IP(x, y, z, w) htonl((t_ip)((x << 24) | (y << 16) | (z << 8) | w))

int	g_received_signal = 0;

MU_TEST(parse_ip_test_loopback) {
	t_ip	ip = 0;
	char	*ip_str = "127.0.0.1";
	t_ip	expected_ip = IP(127, 0, 0, 1);
	
	mu_assert_int_eq(parse_ip_addr(ip_str, &ip), 0);
	printf("ip: %x\n", ip);
	printf("expected_ip: %x\n", expected_ip);
	mu_assert(ip == expected_ip, "IP address parsed incorrectly");
}

MU_TEST(parse_ip_test_broadcast)
{
	t_ip	ip = 0;
	char	*ip_str = "255.255.255.255";
	t_ip	expected_ip = IP(255, 255, 255, 255);

	mu_assert_int_eq(parse_ip_addr(ip_str, &ip), 0);
	mu_assert(ip == expected_ip, "IP address parsed incorrectly");
}

MU_TEST(ip_to_str_test_loopback) {
	t_ip	ip = IP(127, 0, 0, 1);
	char	ip_str[INET_ADDRSTRLEN];
	char	*expected_ip_str = "127.0.0.1";

	ip_to_str(ip, ip_str);
	mu_assert_string_eq(ip_str, expected_ip_str);
}


MU_TEST(ip_to_str_broadcast)
{
	t_ip	ip = IP(255, 255, 255, 255);
	char	ip_str[INET_ADDRSTRLEN];
	char	*expected_ip_str = "255.255.255.255";

	ip_to_str(ip, ip_str);
	mu_assert_string_eq(ip_str, expected_ip_str);
}

MU_TEST_SUITE(tests_parse_ip_addr) {
	MU_RUN_TEST(parse_ip_test_loopback);
	MU_RUN_TEST(parse_ip_test_broadcast);
}

MU_TEST_SUITE(tests_ip_to_str) {
  MU_RUN_TEST(ip_to_str_test_loopback);
  MU_RUN_TEST(ip_to_str_broadcast);
}

int	main(void)
{
	MU_RUN_SUITE(tests_parse_ip_addr);
	MU_RUN_SUITE(tests_ip_to_str);
	MU_REPORT();
	return (MU_EXIT_CODE);
}
