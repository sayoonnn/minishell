/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:38:25 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/02 12:42:02 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H

# define CMD 				0
# define ARGV 				1
# define FILENAME 			2
# define PIPE	 			3
# define REDIRECTION	 	4
# define REDIRECTION_LIST 	5
# define REDIRECTION_INFO 	6
# define DLESS				7
# define DGREAT 			8
# define LESS 				9
# define GREAT 				10
# define CMD_INFO 			11

# include <stdio.h>
# include "libft.h"
# include "types.h"

t_parsing	*init_parsing_tool(void);
void		clean_parsing_tools(t_parsing *parsing);
void		free_parsing(t_parsing *parsing);

int			is_white(char ch);
int			is_quote(char ch);
int			is_operator(char ch);
int			is_brack(char ch);
int			check_rquote(char *cmd, size_t *idx, size_t *new_len);

int			select_parse_tree_token_type(int token_type);
t_tree_node	*create_tree_node(int token_type);
int			connect_cmd_argv_content(t_tree_node **root, t_parsing *parsing);
int			insert_cmd_info_token(t_tree_node **root, t_parsing *parsing);
int			insert_redirection_info(t_tree_node **root, t_deque *tokens);

int			tokenize(char *cmd, t_parsing *parsing);
int			analyze_syntax(t_parsing *parsing);
int			select_word_token_type(t_deque *tokens, int *cmd_flag);
int			parse_line(char *line, t_parsing *parsing);

#endif
