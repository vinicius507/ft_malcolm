# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vgoncalv <vgoncalv@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/02 15:23:08 by vgoncalv          #+#    #+#              #
#    Updated: 2024/07/02 23:33:34 by vgoncalv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=ft_malcolm

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = ./src
OBJS_DIR = ./build
TESTS_DIR = ./tests

vpath %.c $(SRCS_DIR) $(TESTS_DIR)
SRCS = main.c addr.c cli.c error.c poison.c interface.c arp.c
OBJS = $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

TESTS_SRCS = $(filter-out main.c, $(SRCS)) test_main.c
TESTS_OBJS = $(addprefix $(OBJS_DIR)/, $(TESTS_SRCS:.c=.o))

ifneq ($(LIBFT_DIR),)
	CFLAGS += -I $(LIBFT_DIR)/include
	LIBFT = $(LIBFT_DIR)/libft.a
endif

all: $(NAME)

ifeq ($(LIBFT_DIR),)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lft

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -f $(NAME)
else
$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME) run_tests
endif

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir -p $@

re: fclean all

tests: $(NAME) $(TESTS_OBJS)
	$(CC) $(CFLAGS) -o run_tests $(TESTS_OBJS) -L. -lft

.PHONY: all clean fclean re tests
