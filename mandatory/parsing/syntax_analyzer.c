/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:45:15 by devpark           #+#    #+#             */
/*   Updated: 2024/01/02 00:19:48 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"
#include "errors.h"

int	insert_pipeline(t_tree_node **root, t_deque *tokens, t_parsing *parsing)
{
	t_tree_node	*tmp;

	if (*root == NULL)
		return (print_syntax_token_error(tokens->front->content));
	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (tokens->front->right->token_type == PIPE)
		return (print_syntax_token_error(tokens->front->right->content));
	tmp = create_tree_node(deque_front(tokens));
	if (tmp == NULL)
		return (1);
	tmp->left = *root;
	*root = tmp;
	deque_pop_front(tokens);
	parsing->cmd_info_ptr = NULL;
	return (0);
}

int	insert_redirection_list(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	t_tree_node	*rd;
	t_tree_node	*tmp;

	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (tokens->front->right->token_type != FILENAME)
		return (print_syntax_token_error(tokens->front->right->content));
	if (*root == NULL
		|| ((*root)->token_type == PIPE && (*root)->right == NULL))
	{
		if (insert_cmd_info_token(root, ps))
			return (1);
	}
	tmp = *root;
	while (tmp->right != NULL)
		tmp = tmp->right;
	rd = create_tree_node(tokens->front->token_type);
	if (rd == NULL)
		return (1);
	tmp->right = rd;
	if (insert_redirection_info(&tmp->right, tokens))
		return (1);
	return (0);
}

int	check_word_syntax_error(t_tree_node **root, t_parsing *parsing)
{
	char	quote;
	char	quote_flag;
	size_t	idx;

	idx = 0;
	quote = 0;
	quote_flag = 0;
	while (parsing->tokens->front->content[idx] != 0)
	{
		if (is_quote(parsing->tokens->front->content[idx]))
		{
			quote_flag = 1;
			quote = parsing->tokens->front->content[idx++];
			while (parsing->tokens->front->content[idx] != quote
				&& parsing->tokens->front->content[idx] != 0)
				idx++;
			if (parsing->tokens->front->content[idx] == 0)
				break ;
		}
		quote_flag = 0;
		idx++;
	}
	if (quote_flag)
		return (print_syntax_unmatched_error(quote));
	return (connect_cmd_argv_content(root, parsing));
}

int	analyze_syntax(t_parsing *ps)
{
	int		token_type;
	int		check;

	while (!deque_empty(ps->tokens))
	{
		token_type = deque_front(ps->tokens);
		if (token_type == CMD || token_type == ARGV)
			check = check_word_syntax_error(&ps->root, ps);
		else if (token_type == REDIRECTION)
			check = insert_redirection_list(&ps->root, ps->tokens, ps);
		else if (token_type == PIPE)
			check = insert_pipeline(&ps->root, ps->tokens, ps);
		if (check)
			return (check);
	}
	return (0);
}
