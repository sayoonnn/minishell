
NAME	=	minishell

BUILTIN	=	ft_cd.c\
			ft_echo.c\
			ft_env.c\
			ft_exit.c\
			ft_export.c\
			ft_export_utils.c\
			ft_pwd.c\
			ft_unset.c

EXECVE	=	exec_single.c\
			excute_hub.c\
			exec_bin.c\
			exec_utils.c\
			exec_builtin.c\
			exec_pipe.c\
			exec_redir.c\
			heredoc.c\
			redirection.c

PARSING	=	parsing_init.c\
			parsing_cleaner.c\
			parse_line.c\
			parsing_utils.c\
			syntax_analyzer.c\
			syntax_analyzer2.c\
			syntax_analyzer_utils.c\
			syntax_error.c\
			tokenizer.c\
			tokenizer_utils.c

UTILS	=	envp_utils.c\
			envtree_func.c\
			envtree_func2.c\
			reset_io.c\
			signal_handler.c\
			minishell_utils.c

SUBS	=	convert_word_lst_to_array.c\
			ft_split_white.c\
			quotes_remover.c\
			word_interpreter_utils.c\
			word_interpreter.c

SRC		=	main.c\
			$(BUILTIN)\
			$(EXECVE)\
			$(PARSING)\
			$(UTILS)\
			$(SUBS)

OBJDIR	=	.objs
OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

DIR		=	mandatory

vpath %.c	$(addprefix $(DIR), /.\
			$(addprefix /builtin, /.)\
			$(addprefix /execve, /.)\
			$(addprefix /parsing, /.)\
			$(addprefix /substitution, /.)\
			$(addprefix /utils, /.))

INC		= $(DIR)/includes

LIBFT	= libft
LIBFTA	= libft/libft.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

ifdef BONUS
	DIR	= bonus
endif

all :
	@make $(NAME) -j8

bonus :
	@make BONUS=1 all

$(NAME): $(OBJ) $(LIBFTA)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFTA) -o $@ -lreadline
	@echo $(NAME) DONE ✅ 

$(LIBFTA):
	@make -C $(LIBFT)
	@echo LIBFT DONE ✅

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@$(CC) $(CFLAGS) -I $(INC) -c $< -o $@

$(OBJDIR):
	@mkdir $(OBJDIR)

clean:
	@make -C $(LIBFT) clean
	@rm -rf $(OBJDIR)
	@echo CLEAN DONE ✅

fclean:
	@make clean
	@make -C $(LIBFT) fclean
	@rm -f $(NAME) $(BONUS)
	@echo FCLEAN DONE ✅

re: 
	@make fclean
	@make all

.PHONY:	all bonus clean fclean re
