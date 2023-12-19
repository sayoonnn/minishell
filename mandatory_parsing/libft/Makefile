# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/15 17:52:01 by jonghopa          #+#    #+#              #
#    Updated: 2023/12/18 23:06:22 by jonghopa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -g3 -Wall -Wextra -Werror
NAME = libft.a
SRCS_L = \
ft_isalpha.c \
ft_isdigit.c \
ft_isalnum.c \
ft_isascii.c \
ft_isprint.c \
ft_strlen.c \
ft_memset.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_toupper.c \
ft_tolower.c \
ft_strchr.c \
ft_strrchr.c \
ft_strncmp.c \
ft_strnstr.c \
ft_atoi.c \
ft_calloc.c \
ft_strdup.c

SRCS_A = \
ft_substr.c \
ft_strjoin.c \
ft_strtrim.c \
ft_itoa.c \
ft_putchar_fd.c \
ft_putstr_fd.c \
ft_putendl_fd.c \
ft_putnbr_fd.c \

OBJS = $(SRCS_L:.c=.o) $(SRCS_A:.c=.o)

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
