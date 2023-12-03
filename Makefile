NAME	= minishell
SRC		= built_in/ft_env.c built_in/ft_export.c built_in/env_tree_func.c tmp.c\
		  built_in/ft_unset.c
OBJ		= $(SRC:.c=.o)

INC		= ./includes

LIBFT	= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra 
#-fsanitize=address

all :
	@make $(NAME) -j4

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@
	@echo $(NAME) DONE ✅ 

$(LIBFT):
	@make -C libft
	@echo LIBFT DONE ✅

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

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
