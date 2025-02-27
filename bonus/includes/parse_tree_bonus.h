/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:38:25 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/05 14:26:42 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_BONUS_H
# define PARSE_TREE_BONUS_H
# define CMD 0
# define ARGV 1
# define FILENAME 2
# define PIPE 3
# define REDIRECTION 4
# define LIST 5
# define SUBSHELL 6
# define LPAREN 7
# define RPAREN 8
# define REDIRECTION_LIST 9
# define REDIRECTION_INFO 10
# define CMD_INFO 11
# define DLESS 12
# define DGREAT 13
# define LESS 14
# define GREAT 15
# define AND 16
# define OR 17

# include <stdio.h>
# include "libft_bonus.h"
# include "types_bonus.h"

t_parsing	*init_parsing_tool(void);
int			parse_line(char *line, t_parsing *parsing);
void		clean_parsing_tools(t_parsing *parsing);
void		free_parsing(t_parsing *parsing);

int			is_white(char ch);
int			is_quote(char ch);
int			is_parenthesis(char ch);
int			is_operator(char *cmd, size_t idx);

int			print_syntax_token_error(char *content);
int			print_syntax_unmatched_error(char ch);
t_tree_node	*create_tree_node(int token_type);
int			check_rparen(t_parsing *ps);
int			check_subshell(t_tree_node **root);
int			start_subshell(t_tree_node **root, t_deque *tokens, t_parsing *ps);
int			end_subshell(t_tree_node **root, t_deque *tokens, t_parsing *ps);
int			insert_operator(t_tree_node **root, t_deque *tokens, t_parsing *ps);
int			insert_cmd_info_token(t_tree_node **root, t_parsing *ps);
int			insert_rd_list(t_tree_node **root, t_deque *tokens, t_parsing *ps);
int			analyze_syntax(t_tree_node **root, t_parsing *ps);

int			select_paren_token_type(char *paren);
int			select_opr_token_type(char *operator);
int			select_word_token_type(t_deque *tokens, int *cmd_flag);
int			tokenize(char *cmd, t_parsing *parsing);
int			check_rquote(char *cmd, size_t *idx, size_t *new_len);

#endif
