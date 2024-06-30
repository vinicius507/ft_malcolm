# 42 Malcolm

An ARP Poisoning tool written in C with the 99 standard.

> [!NOTE]
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

1. Clone the ft_malcolm repository:

   ```bash
   git clone https://github.com/vinicius507/ft_malcolm.git
   ```

2. Navigate to the project directory:

   ```bash
   cd ft_malcolm
   ```

3. Clone the Libft repository:

   ```bash
   git clone https://github.com/vinicius507/libft.git
   ```

4. Build the library:

   ```bash
   make -C ./libft
   ```

5. Build the tool:

   ```bash
   make LIBFT_DIR=./libft/libft -C ./ft_malcolm
   ```

### Building with Nix

If you prefer using Nix, you can build the application by navigating to the
project directory and using the following command:

```bash
nix build .#
```

This assumes you have a valid Nix environment set up. The build process will
handle downloading and linking dependencies automatically.
