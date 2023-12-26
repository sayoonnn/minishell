/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:38:25 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 14:47:49 by devpark          ###   ########.fr       */
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
# include "deque.h"
# include "list.h"

typedef struct s_tree_node
{
	int					token_type;
	t_list				*contents;
	int					fd[2];
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}				t_tree_node;

typedef struct s_parsing
{
	int			cmd_flag;
	int			detach;
	t_deque		*tokens;
	t_list		*argv_lst;
	t_tree_node	*root;
	t_tree_node	*cmd_info_ptr;
}				t_parsing;

t_parsing	*init_parsing_tool(void);
void		clean_parsing_tools(t_parsing *parsing);
void		free_parsing(t_parsing *parsing);

int			print_syntax_token_error(char *content);
int			print_syntax_unmatched_error(char ch);

int			is_white(char ch);
int			is_quote(char ch);
int			is_operator(char ch);
char		*make_word(char *cmd, size_t *idx, size_t len);
int			free_perfectly_split(char **strs);
int			check_rquote(char *cmd, size_t *idx, size_t *new_len);

int			tokenize(char *cmd, t_parsing *data);
int			analyze_syntax(t_parsing *data);
t_tree_node	*parse_line(char *line, t_parsing *parsing);

#endif
