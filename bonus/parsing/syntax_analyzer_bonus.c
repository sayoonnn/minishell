/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:45:15 by devpark           #+#    #+#             */
/*   Updated: 2024/01/04 17:27:28 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	connect_cmd_argv_content(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	t_node	*new;
	char	*content;

	if (*root == NULL || (((*root)->token_type == PIPE \
	|| ((*root)->token_type == AND || (*root)->token_type == OR)) \
	&& (*root)->right == NULL) || (((*root)->token_type == AND \
	|| (*root)->token_type == OR) && (*root)->right->token_type == PIPE \
	&& (*root)->right->right == NULL))
	{
		if (insert_cmd_info_token(root, ps))
			return (1);
	}
	content = ft_strdup(tokens->front->content);
	new = ft_lstnew(content);
	if (content == NULL || new == NULL)
	{
		if (content)
			free(content);
		return (1);
	}
	ft_lstadd_back(ps->cmd_info_ptr->contents, new);
	deque_pop_front(tokens);
	return (0);
}

int	check_word_syntax_error(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	char	quote;
	char	quote_flag;
	size_t	idx;

	idx = 0;
	quote = 0;
	quote_flag = 0;
	while (tokens->front->content[idx] != 0)
	{
		if (is_quote(tokens->front->content[idx]))
		{
			quote_flag = 1;
			quote = tokens->front->content[idx++];
			while (tokens->front->content[idx] != quote
				&& tokens->front->content[idx] != 0)
				idx++;
			if (tokens->front->content[idx] == 0)
				break ;
		}
		quote_flag = 0;
		idx++;
	}
	if (quote_flag)
		return (print_syntax_unmatched_error(quote));
	return (connect_cmd_argv_content(root, tokens, ps));
}

int	analyze_syntax(t_tree_node **root, t_parsing *ps)
{
	int	token_type;
	int	check;

	while (!deque_empty(ps->tokens))
	{
		token_type = deque_front(ps->tokens);
		if (token_type == LPAREN)
			check = start_subshell(root, ps->tokens, ps);
		else if (token_type == RPAREN)
		{
			check = end_subshell(root, ps->tokens, ps);
			if (check == 0)
				break ;
		}
		else if (token_type == CMD || token_type == ARGV)
			check = check_word_syntax_error(root, ps->tokens, ps);
		else if (token_type == REDIRECTION)
			check = insert_rd_list(root, ps->tokens, ps);
		else if (token_type == PIPE || token_type == LIST)
			check = insert_operator(root, ps->tokens, ps);
		if (check)
			return (check);
	}
	return (check_rparen(ps));
}
