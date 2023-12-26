/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:45:15 by devpark           #+#    #+#             */
/*   Updated: 2023/12/26 13:46:56 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	select_parse_tree_token_type(int token_type)
{
	if (token_type == REDIRECTION)
		return (REDIRECTION_LIST);
	else if (token_type == REDIRECTION_LIST)
		return (REDIRECTION_INFO);
	return (token_type);
}

t_tree_node	*create_tree_node(int token_type)
{
	t_tree_node	*syntax_node;

	syntax_node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (syntax_node == NULL)
		return (NULL);
	syntax_node->token_type = select_parse_tree_token_type(token_type);
	syntax_node->contents = NULL;
	syntax_node->left = NULL;
	syntax_node->right = NULL;
	return (syntax_node);
}

int	insert_pipeline(t_tree_node **root, t_deque *tokens, t_parsing *data)
{
	t_tree_node	*tmp;

	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (*root == NULL || tokens->front->right->token_type == PIPE)
		return (print_syntax_token_error("|"));
	tmp = create_tree_node(deque_front(tokens));
	if (tmp == NULL)
		return (1);
	tmp->left = *root;
	*root = tmp;
	deque_pop_front(tokens);
	data->cmd_info_ptr = NULL;
	return (0);
}

int	insert_filename(t_tree_node **root, t_deque *tokens)
{
	t_tree_node	*file;
	t_node		*content;

	content = NULL;
	file = create_tree_node(FILENAME);
	if (file == NULL)
		return (1);
	if (file->contents == NULL)
	{
		file->contents = ft_lstcreate();
		content = ft_lstnew(tokens->front->content);
		if (file->contents == NULL || content == NULL)
		{
			if (file->contents)
				free(file->contents);
			free(file);
			return (1);
		}
	}
	ft_lstadd_back(file->contents, content);
	(*root)->right = file;
	deque_pop_front(tokens);
	return (0);
}

int	insert_redirection_type(t_tree_node **root, t_deque *tokens)
{
	t_tree_node	*rd_real;
	char		*rd_content;
	int			token_type;

	rd_content = tokens->front->content;
	token_type = 0;
	if (!ft_strncmp(rd_content, "<<", 2))
		token_type = DLESS;
	else if (!ft_strncmp(rd_content, ">>", 2))
		token_type = DGREAT;
	else if (!ft_strncmp(rd_content, "<", 1))
		token_type = LESS;
	else if (!ft_strncmp(rd_content, ">", 1))
		token_type = GREAT;
	rd_real = create_tree_node(token_type);
	if (rd_real == NULL)
		return (1);
	(*root)->left = rd_real;
	deque_pop_front(tokens);
	return (0);
}

int	insert_redirection_info(t_tree_node **root, t_deque *tokens)
{
	t_tree_node	*rd_info;

	rd_info = create_tree_node((*root)->token_type);
	if (rd_info == NULL)
		return (1);
	(*root)->left = rd_info;
	if (insert_redirection_type(&(*root)->left, tokens))
		return (1);
	if (insert_filename(&(*root)->left, tokens))
		return (1);
	return (0);
}

int	insert_cmd_info_token(t_tree_node **root, t_parsing *data)
{
	t_tree_node	*cmd;
	t_tree_node	*cmd_info;

	cmd = create_tree_node(CMD);
	if (cmd == NULL)
		return (1);
	if (*root == NULL)
		*root = cmd;
	if ((*root)->token_type == PIPE && (*root)->right == NULL)
		(*root)->right = cmd;
	cmd_info = create_tree_node(CMD_INFO);
	if (cmd_info == NULL)
		return (1);
	cmd->left = cmd_info;
	cmd_info->contents = ft_lstcreate();
	if (cmd_info->contents == NULL)
		return (1);
	data->cmd_info_ptr = cmd_info;
	return (0);
}

int	insert_redirection_list(t_tree_node **root, t_deque *tokens, t_parsing *data)
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
		if (insert_cmd_info_token(root, data))
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

int	connect_cmd_argv_content(t_tree_node **root, t_parsing *data)
{
	t_node	*new;
	char	*content;

	if (*root == NULL
		|| ((*root)->token_type == PIPE && (*root)->right == NULL))
	{
		if (insert_cmd_info_token(root, data))
			return (1);
	}
	content = ft_strdup(data->tokens->front->content);
	new = ft_lstnew(content);
	if (content == NULL || new == NULL)
	{
		if (content)
			free(content);
		return (1);
	}
	ft_lstadd_back(data->cmd_info_ptr->contents, new);
	deque_pop_front(data->tokens);
	return (0);
}

int	check_word_syntax_error(t_tree_node **root, t_parsing *data)
{
	char	quote;
	char	quote_flag;
	size_t	idx;

	idx = 0;
	quote = 0;
	quote_flag = 0;
	while (data->tokens->front->content[idx] != 0)
	{
		if (is_quote(data->tokens->front->content[idx]))
		{
			quote_flag = 1;
			quote = data->tokens->front->content[idx++];
			while (data->tokens->front->content[idx] != quote
				&& data->tokens->front->content[idx] != 0)
				idx++;
			if (data->tokens->front->content[idx] == 0)
				break ;
		}
		quote_flag = 0;
		idx++;
	}
	if (quote_flag)
		return (print_syntax_unmatched_error(quote));
	return (connect_cmd_argv_content(root, data));
}

int	analyze_syntax(t_parsing *data)
{
	int		token_type;
	int		check;

	while (!deque_empty(data->tokens))
	{
		token_type = deque_front(data->tokens);
		if (token_type == CMD || token_type == ARGV)
			check = check_word_syntax_error(&data->root, data);
		else if (token_type == REDIRECTION)
			check = insert_redirection_list(&data->root, data->tokens, data);
		else if (token_type == PIPE)
			check = insert_pipeline(&data->root, data->tokens, data);
		if (check)
			return (check);
	}
	return (0);
}
