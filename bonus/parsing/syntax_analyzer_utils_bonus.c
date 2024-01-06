/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:12:25 by devpark           #+#    #+#             */
/*   Updated: 2024/01/04 17:17:46 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_tree_node	*create_tree_node(int token_type)
{
	t_tree_node	*syntax_node;

	syntax_node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (syntax_node == NULL)
		return (NULL);
	syntax_node->token_type = token_type;
	syntax_node->contents = NULL;
	syntax_node->left = NULL;
	syntax_node->mid = NULL;
	syntax_node->right = NULL;
	syntax_node->fd[0] = 0;
	syntax_node->fd[1] = 1;
	return (syntax_node);
}

int	check_rparen(t_parsing *ps)
{
	if (deque_empty(ps->tokens) && ps->subsh_cnt > 0)
		return (print_syntax_unmatched_error(')'));
	return (0);
}

int	check_subshell(t_tree_node **root)
{
	if (*root == NULL)
		return (0);
	if (((*root)->token_type == AND || (*root)->token_type == OR) \
	&& (*root)->right == NULL)
		return (0);
	return (1);
}
