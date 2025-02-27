/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_subshell_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:18:35 by devpark           #+#    #+#             */
/*   Updated: 2024/01/09 12:14:54 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	insert_subshell(t_tree_node **root, t_parsing *ps)
{
	t_tree_node	*subsh;

	subsh = create_tree_node(SUBSHELL);
	if (subsh == NULL)
		return (1);
	if (*root == NULL)
		*root = subsh;
	else if (((*root)->token_type == PIPE || (*root)->token_type == OR \
	|| (*root)->token_type == AND) && (*root)->right == NULL)
		(*root)->right = subsh;
	else if (((*root)->token_type == OR || (*root)->token_type == AND \
	|| (*root)->right->token_type == PIPE) && (*root)->right->right == NULL)
		(*root)->right->right = subsh;
	ps->subsh_cnt += 1;
	deque_pop_front(ps->tokens);
	return (analyze_syntax(&subsh->mid, ps));
}

int	start_subshell(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	if (check_subshell(root))
		return (print_syntax_token_error(tokens->front->content));
	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (tokens->front->right->token_type == LIST
		|| tokens->front->right->token_type == PIPE
		|| tokens->front->right->token_type == RPAREN)
		return (print_syntax_token_error(tokens->front->right->content));
	return (insert_subshell(root, ps));
}

int	end_subshell(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	if (*root == NULL || ps->subsh_cnt == 0)
		return (print_syntax_token_error(tokens->front->content));
	if (tokens->front->right != NULL
		&& (tokens->front->right->token_type != LIST
			&& tokens->front->right->token_type != RPAREN))
		return (print_syntax_token_error(tokens->front->right->content));
	ps->subsh_cnt -= 1;
	deque_pop_front(tokens);
	return (0);
}
