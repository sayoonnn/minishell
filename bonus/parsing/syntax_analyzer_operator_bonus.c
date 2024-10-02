/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_operator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:24:59 by devpark           #+#    #+#             */
/*   Updated: 2024/01/04 17:25:04 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	insert_list(t_tree_node **root, t_deque *tokens)
{
	t_tree_node	*list_node;
	int			token_type;

	token_type = 0;
	if (!ft_strncmp(tokens->front->content, "&&", 2))
		token_type = AND;
	else
		token_type = OR;
	list_node = create_tree_node(token_type);
	if (list_node == NULL)
		return (1);
	list_node->left = *root;
	*root = list_node;
	return (0);
}

int	insert_pipeline(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	t_tree_node	*pipe_node;

	if ((*root)->token_type == AND || (*root)->token_type == OR)
		return (insert_pipeline(&(*root)->right, tokens, ps));
	pipe_node = create_tree_node(PIPE);
	if (pipe_node == NULL)
		return (1);
	if ((*root)->token_type == CMD || (*root)->token_type == PIPE)
	{
		pipe_node->left = *root;
		(*root) = pipe_node;
	}
	return (0);
}

int	insert_operator(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	if (*root == NULL)
		return (print_syntax_token_error(tokens->front->content));
	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (tokens->front->right->token_type == PIPE
		|| tokens->front->right->token_type == LIST
		|| tokens->front->right->token_type == RPAREN)
		return (print_syntax_token_error(tokens->front->right->content));
	if (tokens->front->token_type == PIPE)
	{
		if (insert_pipeline(root, tokens, ps))
			return (1);
	}
	else
	{
		if (insert_list(root, tokens))
			return (1);
	}
	ps->cmd_info_ptr = NULL;
	deque_pop_front(tokens);
	return (0);
}
