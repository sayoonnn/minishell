/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:38:25 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/19 14:44:34 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H
# define CMD 0
# define ARGV 1
# define FILENAME 2
# define PIPELINE 3
# define REDIRECTION 4
# define REDIRECTION_LIST 5
# define REDIRECTION_INFO 6
# define DLESS 7
# define DGREAT 8
# define LESS 9
# define GREAT 10
# define CMD_INFO 11

# include <stdio.h>
# include "libft.h"
# include "deque.h"
# include "argv_list.h"

typedef struct s_tree_node
{
	int					token_type;
	char				**contents;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}				t_tree_node;

typedef struct s_data
{
	int			cmd_flag;
	int			detach;
	t_deque		*tokens;
	t_list		*argv_lst;
	t_tree_node	*root;
}				t_data;

int		is_white(char ch);
int		is_quote(char ch);
int		is_operator(char ch);
int		free_perfectly_split(char **strs);
char	*make_word(char *cmd, size_t *idx, size_t len);
int		link_argv(t_data *data, char *argv);
int		link_argv_to_lst(t_data *data, char **strs, char *value);
int		process_special_dollar(t_data *data, char *word, size_t *idx);
int		analyze_cmd_argv(t_data *data, char *word);
int		analyze_syntax(t_data *data);
int		tokenize(char *cmd, t_data *data);

int		select_word_token_type(t_data *data);
int		check_rquote(char *cmd, size_t *idx, size_t *new_len);
int		init_data(t_data *data);
void	free_data(t_data *data);

int		print_syntax_token_error(char *content);
int		print_syntax_unmatched_error(char ch);

#endif
