/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 16:04:27 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:41:12 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_BONUS_H
# define TYPES_BONUS_H

enum	e_success
{
	success,
	fail
};

enum	e_bool
{
	false,
	true
};

typedef struct s_deque_node
{
	int					token_type;
	char				*content;
	struct s_deque_node	*left;
	struct s_deque_node	*right;
}			t_deque_node;

typedef struct s_deque
{
	t_deque_node	*front;
	t_deque_node	*back;
}			t_deque;

typedef struct s_node
{
	char			*content;
	struct s_node	*next;
}				t_node;

typedef struct s_list
{
	t_node	*head;
	t_node	*tail;
}				t_list;

typedef struct s_envnode
{
	char				*key;
	char				*value;
	char				*forarr;
	struct s_envnode	*left;
	struct s_envnode	*right;
}				t_envnode;

typedef struct s_envtree
{
	int			num_nodes;
	t_envnode	*root;
}				t_envtree;

typedef struct s_tree_node
{
	int					token_type;
	t_list				*contents;
	struct s_tree_node	*left;
	struct s_tree_node	*mid;
	struct s_tree_node	*right;
	int					cmd_cnt;
	int					fd[2];
}				t_tree_node;

typedef struct s_parsing
{
	int			cmd_flag;
	int			subsh_cnt;
	t_deque		*tokens;
	t_tree_node	*root;
	t_tree_node	*cmd_info_ptr;
}				t_parsing;

#endif
