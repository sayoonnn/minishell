# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 14:56:11 by jonghopa          #+#    #+#              #
#    Updated: 2023/12/18 23:06:15 by jonghopa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror

NAME = deque.a
SRCS = \
deque_create.c \
deque_create_node.c \
deque_push_front.c \
deque_push_back.c \
deque_pop_front.c \
deque_pop_back.c \
deque_front.c \
deque_back.c \
deque_size.c \
deque_empty.c \
deque_clear.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@ar -rcs $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $^

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: 
	@make fclean
	@make all

.PHONY: all clean fclean re
