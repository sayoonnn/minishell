NAME	= minishell
SRC		= main.c utils/signal_handler.c utils/envp_utils.c utils/envtree_func.c\
		  built_in/ft_env.c utils/envtree_func2.c built_in/ft_cd.c built_in/ft_export.c
OBJ		= $(SRC:.c=.o)

INC		= ./includes

LIBFT	= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -fsanitize=address

all :
	@make $(NAME) -j4

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $@ -lreadline
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

fclean:
	@make clean
	@make -C libft fclean
	@rm -f $(NAME)
	@echo FCLEAN DONE ✅

re: 
	@make fclean
	@make all

.PHONY:	all bonus clean fclean re
