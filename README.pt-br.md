# 42 Malcolm

![OS](https://img.shields.io/badge/OS-Linux-blue.svg)
![Language](https://img.shields.io/badge/Language-C-orange.svg)
![Status](https://img.shields.io/badge/Status-Pending_Evaluation-darkgrey.svg?logo=42)
[![Tests](https://github.com/vinicius507/ft_malcolm/actions/workflows/tests.yml/badge.svg)](https://github.com/vinicius507/ft_malcolm/actions/workflows/tests.yml)

[![en](https://img.shields.io/badge/Lang-en-red.svg)](./README.md)
[![pt-br](https://img.shields.io/badge/Lang-pt--br-green.svg)](./README.pt-br.md)

Uma ferramenta de ARP Poisoning escrita em C usando o padrão 99.

> [!WARNING]
>
> Esta aplicação realiza ARP spoofing, uma técnica de ataque que pode
> interromper a comunicação em uma rede. Utilizar ARP spoofing sem permissão é
> uma violação de políticas de segurança e pode ser ilegal. É crucial usar esta
> ferramenta apenas em ambientes controlados, como uma rede de laboratório
> pessoal, para fins educativos ou de teste.
> 
> Esta ferramenta foi criada como parte do currículo de Segurança da École 42 e
> destina-se apenas a fins educativos. O autor não apoia nem encoraja o uso
> desta ferramenta para fins maliciosos.

## O que é ARP?

O Address Resolution Protocol é um protocolo da Camada 2 que mapeia endereços
de hardware, como um endereço MAC, para um endereço de protocolo da Camada 3,
como um endereço IPv4.

## Como funciona o ARP poisoning?

O protocolo ARP é um protocolo _stateless_, o que significa que os hosts da
rede armazenarão em cache automaticamente qualquer resposta ARP que receberem,
independentemente de ter sido solicitada ou não.

O ARP poisoning funciona enviando respostas ARP não solicitadas a um host,
associando um endereço de protocolo ao endereço de hardware do atacante.

## Uso

### Compilando a partir do código-fonte

**Requisitos:**

- Clang 12
- GNU Make
- [Minha biblioteca Libft](https://github.com/vinicius507/libft)

**Instruções:**

1. Clone o repositório do 42 Malcolm:

   ```bash
   git clone https://github.com/vinicius507/ft_malcolm.git


2. Clone o repositório da Libft:

   ```bash
   git clone https://github.com/vinicius507/libft.git
   ```

3. Navegue até o diretório do projeto:

   ```bash
   cd ft_malcolm
   ```

4. Compile a ferramenta:

   ```bash
   make LIBFT_DIR=../libft/libft -C ./ft_malcolm # Ajuste o caminho, se necessário
   ```

### Compilando com Nix

Se preferir usar Nix, você pode compilar a aplicação navegando até o diretório
do projeto e usando o seguinte comando:

```bash
nix build .#
```

Isso assume que você tem um ambiente Nix válido configurado. O processo de
compilação lidará automaticamente com o download e _linkagem_ das dependências.

### Executando a Aplicação

**Antes de executar:**

- Certifique-se de ter **permissão explícita** para executar esta ferramenta na
rede alvo.
- Esteja ciente do impacto potencial do ARP poisoning na rede.

**Executando a ferramenta:**

> [!NOTE]
> 
> É necessário ter privilégios de root para executar a aplicação.

```bash
./ft_malcolm [OPÇÃO...] IP_FONTE MAC_FONTE IP_ALVO MAC_ALVO
```

**Argumentos Posicionais:**

- `IP_FONTE`: O endereço IP a ser falsificado como fonte.
- `MAC_FONTE`: O endereço MAC a ser falsificado como fonte.
- `IP_ALVO`: O endereço IP do dispositivo alvo.
- `MAC_ALVO`: O endereço MAC do dispositivo alvo.

**Argumentos Opcionais:**

- `-g, --gratuitous`: Enviar um pacote ARP gratuito para broadcast
(`FF:FF:FF:FF:FF:FF`).
- `-i, --interface`: A interface de rede a ser usada, se não especificada, a
primeira interface disponível será utilizada.
- `-v, --verbose`: Ativar saída detalhada para informações do pacote.

**Exemplo:**

```bash
./ft_malcolm 192.168.122.67 AA:BB:CC:DD:EE:FF 192.168.122.206 00:11:22:33:44:55
```
```
