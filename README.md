# 42 Malcolm

An ARP Poisoning tool written in C with the 99 standard.

> [!WARNING]
>
> This tool is for educational purposes only. ARP Poisoning is a technique used
> in Man-in-the-Middle (MitM) attacks. It's crucial to understand the potential
> risks and only use this tool in controlled environments with explicit
> permission.

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

- `-g, --gratuious`: Send a gratuitous ARP packet to broadcast (ff:ff:ff:ff:ff:ff).
- `-h, --help`: Show the help message and exit.
- `-i, --interface`: The network interface to use, if not specified, the first
available interface will be used.
- `-v, --verbose`: Enable verbose output for packet information.

**Example:**

```bash
./ft_malcolm 192.168.122.67 AA:BB:CC:DD:EE:FF 192.168.122.206 00:11:22:33:44:55
```
