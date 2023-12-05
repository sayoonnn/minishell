NAME	=	minishell
SRC		=	main.c\
			builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_unset.c\
			builtin/ft_exit.c builtin/ft_export.c builtin/ft_pwd.c\
			utils/envtree_func.c utils/envtree_func2.c utils/envp_utils.c utils/signal_handler.c\
			execve/execve_utils.c execve/execve.c\
			utils/print_err.c
OBJ		= $(SRC:.c=.o)

INC		= ./includes

LIBFT	= libft/libft.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -fsanitize=address -g

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
