# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/25 23:34:55 by lserghin          #+#    #+#              #
#    Updated: 2025/05/19 22:53:39 by lserghin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -I./includes

OBJS_DIR = object

SRCS = source/main.c source/inits.c source/utils.c source/philo.c source/monitor.c
OBJS = $(SRCS:source/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: source/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJS_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
