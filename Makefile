NAME	=	minishell
SRC		=	builtin/ft_cd.c builtin/ft_echo.c builtin/ft_env.c builtin/ft_exit.c\
			builtin/ft_export.c builtin/ft_pwd.c builtin/ft_unset.c\
			\
			execve/exec_single.c execve/excute_hub.c execve/exec_bin.c execve/exec_utils.c\
			execve/exec_builtin.c execve/heredoc.c execve/redirection.c execve/exec_redir.c\
			execve/exec_pipe.c\
			\
			parsing/parsing_init.c parsing/parsing_cleaner.c\
			parsing/parse_line.c parsing/parsing_utils.c\
			parsing/syntax_analyzer.c parsing/syntax_analyzer2.c\
			parsing/syntax_analyzer_utils.c\
			parsing/syntax_error.c parsing/tokenizer.c parsing/tokenizer_utils.c\
			\
			utils/envp_utils.c utils/envtree_func.c utils/envtree_func2.c\
			utils/reset_io.c utils/signal_handler.c utils/minishell_utils.c\
			\
			substitution/convert_word_lst_to_array.c substitution/ft_split_white.c\
			substitution/quotes_remover.c substitution/word_interpreter_utils.c\
			substitution/word_interpreter.c\
			\
			main.c

OBJ		=	$(SRC:.c=.o)

INC		= ./includes

LIBFT	= libft/libft.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra 
#-g -fsanitize=address

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
