NAME	=	minishell
SRC		=	builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_exit.c\
			builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c\
			\
			execve/exec_single.c execve/excute_hub.c execve/exec_bin.c execve/exec_utils.c\
			execve/exec_builtin.c execve/heredoc.c execve/redirection.c execve/exec_redir.c\
			execve/exec_pipe.c\
			\
			parsing/cmd_argv_analyzer_utils.c parsing/cmd_argv_analyzer.c parsing/init_free.c\
			parsing/parse_line.c parsing/parsing_utils.c parsing/syntax_analyzer.c\
			parsing/syntax_error.c parsing/tokenizer.c parsing/tokenizer_utils.c\
			\
			utils/envp_utils.c utils/envtree_func.c utils/envtree_func2.c utils/print_err.c\
			utils/reset_io.c utils/signal_handler.c\
			\
			main.c

OBJ		=	$(SRC:.c=.o)

INC		= ./includes

LIBFT	= libft/libft.a
DEQUE	= deque/deque.a
LIST	= argv_list/argv_list.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
# -g -fsanitize=address

all :
	@make $(NAME) -j4

$(NAME): $(OBJ) $(LIBFT) $(DEQUE) $(LIST)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(DEQUE) $(LIST) -o $@ -lreadline
	@echo $(NAME) DONE ✅ 

$(LIBFT):
	@make -C libft
	@echo LIBFT DONE ✅

$(DEQUE):
	@make -C deque;
	@echo DEQUE DONE ✅

$(LIST):
	@make -C argv_list;
	@echo LIST DONE ✅

%.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

clean:
	@make -C libft clean
	@make -C deque clean
	@make -C argv_list clean
	@rm -f $(OBJ)
	@echo CLEAN DONE ✅

fclean:
	@make clean
	@make -C libft fclean
	@make -C deque fclean
	@make -C argv_list fclean
	@rm -f $(NAME)
	@echo FCLEAN DONE ✅

re: 
	@make fclean
	@make all

.PHONY:	all bonus clean fclean re
