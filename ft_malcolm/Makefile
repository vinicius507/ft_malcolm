# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 15:23:08 by vgoncalv          #+#    #+#              #
#    Updated: 2024/06/25 17:11:41 by vgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_malcolm

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = ./src
OBJS_DIR = ./build

vpath %.c $(SRCS_DIR)
SRCS = main.c cli.c error.c poison.c interface.c arp.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lft

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
