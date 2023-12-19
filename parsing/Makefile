# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/13 14:56:11 by jonghopa          #+#    #+#              #
#    Updated: 2023/12/19 15:55:12 by jonghopa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror

NAME = test
LIBFT = ./libft/libft.a
DEQUE = ./deque/deque.a
ARGV_LIST = ./argv_list/argv_list.a

SRCS = \
main.c \
tokenizer.c \
tokenizer_utils.c \
parsing_utils.c \
init_free.c \
cmd_argv_analyzer.c \
cmd_argv_analyzer_utils.c \
syntax_error.c \
syntax_analyzer.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@make -C ./argv_list
	@make -C ./deque
	@$(CC) $(CFLAGS) -o $@ $^ $(LIBFT) $(ARGV_LIST) $(DEQUE)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $^

clean:
	@rm -rf $(OBJS)
	@make -C ./libft/ clean
	@make -C ./argv_list/ clean
	@make -C ./deque/ clean

fclean: clean
	@rm -rf $(NAME) $(LIBFT) $(ARGV_LIST) $(DEQUE)

re:
	@make fclean
	@make all

.PHONY: all clean fclean re
