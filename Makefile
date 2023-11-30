NAME	= minishell
SRC		= ft_cd.c
OBJ		= $(SRC:.c=.o)

LIBFT	= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

all :
	@make $(NAME) -j4

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@
	@echo $(NAME) DONE ✅ 

$(LIBFT):
	@make -C libft
	@echo LIBFT DONE ✅

%.o : %.c minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C libft clean
	@rm -f $(OBJ)
	@echo CLEAN DONE ✅

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo FCLEAN DONE ✅

re: 
	@make fclean
	@make all

.PHONY:	all bonus clean fclean re
