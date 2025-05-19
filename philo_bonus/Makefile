# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lserghin <lserghin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/19 22:55:05 by lserghin          #+#    #+#              #
#    Updated: 2025/05/19 22:57:02 by lserghin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo_bonus

CC = cc
CFLAGS = -Wall -Werror -Wextra
LFLAGS = -I./includes_bonus

OBJS_DIR = object_bonus

SRCS = source_bonus/main.c source_bonus/inits.c source_bonus/utils.c source_bonus/philo.c source_bonus/monitor.c
OBJS = $(SRCS:source_bonus/%.c=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) -o $(NAME)

$(OBJS_DIR)/%.o: source_bonus/%.c
	mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(LFLAGS) -c $< -o $@
	
clean:
	rm -rf $(OBJS_DIR)
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
