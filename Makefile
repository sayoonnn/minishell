
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
			heredoc.c\
			redirection.c\
			redirection_utils.c

PARS	=	parsing_init.c\
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
			word_interpreter.c\
			expansion.c\
			expansion_utils.c

B_BUILTIN	=	$(BUILTIN:%.c=%_bonus.c)

B_EXECVE	=	$(EXECVE:%.c=%_bonus.c)

B_PARS	=	parse_line_bonus.c\
			parsing_utils_bonus.c\
			syntax_analyzer_bonus.c\
			syntax_analyzer_operator_bonus.c\
			syntax_analyzer_redirection_bonus.c\
			syntax_analyzer_subshell_bonus.c\
			syntax_analyzer_utils_bonus.c\
			syntax_error_bonus.c\
			tokenizer_bonus.c\
			tokenizer_utils_bonus.c\
			parsing_cleaner_bonus.c\
			parsing_init_bonus.c

B_UTILS	=	$(UTILS:%.c=%_bonus.c)

B_SUBS	=	$(SUBS:%.c=%_bonus.c)\
			wildcards_bonus.c

M_SRC	=	main.c\
			$(BUILTIN)\
			$(EXECVE)\
			$(PARS)\
			$(UTILS)\
			$(SUBS)

B_SRC	=	main_bonus.c\
			$(B_BUILTIN)\
			$(B_EXECVE)\
			$(B_PARS)\
			$(B_UTILS)\
			$(B_SUBS)


ifdef IS_BONUS
	DIR	= $(BONUS)
	SRC = $(B_SRC)
else
	DIR = $(MAND)
	SRC = $(M_SRC)
endif

OBJDIR	=	.objs
OBJ		=	$(SRC:%.c=$(OBJDIR)/%.o)

MAND	=	mandatory
BONUS	=	bonus

INC		= $(DIR)/includes

LIBFT	= libft
LIBFTA	= libft/libft.a

CC		= cc
CFLAGS	= -Wall -Werror -Wextra

vpath %.c	$(addprefix $(DIR), /.\
			$(addprefix /builtin, /.)\
			$(addprefix /execve, /.)\
			$(addprefix /parsing, /.)\
			$(addprefix /substitution, /.)\
			$(addprefix /utils, /.))

all :
	@make $(NAME) -j8

bonus :
	@make IS_BONUS=1 all

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
	@rm -f $(NAME)
	@echo FCLEAN DONE ✅

re: 
	@make fclean
	@make all

.PHONY:	all bonus clean fclean re
