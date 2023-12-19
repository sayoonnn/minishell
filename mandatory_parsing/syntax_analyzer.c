/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 15:45:15 by devpark           #+#    #+#             */
/*   Updated: 2023/12/18 22:55:23 by jonghopa         ###   ########.fr       */
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

char	**convert_lst_to_array(t_list *lst)
{
	size_t	idx;
	size_t	cnt;
	t_argv	*tmp;
	char	**argvs;

	cnt = 0;
	tmp = lst->head;
	while (tmp != NULL)
	{
		cnt++;
		tmp = tmp->next;
	}
	argvs = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (argvs == NULL)
		return (NULL);
	idx = 0;
	tmp = lst->head;
	while (tmp != NULL)
	{
		argvs[idx++] = tmp->content;
		tmp = tmp->next;
	}
	ft_lstclear(lst, 1);
	return (argvs);
}

int	insert_cmd_info(t_tree_node *root, t_list *lst)
{
	char		**argvs;
	t_tree_node	*cmd_info;
	t_tree_node	*tmp;

	tmp = root;
	if (root->token_type == PIPELINE)
		tmp = root->right;
	cmd_info = create_tree_node(CMD_INFO);
	if (cmd_info == NULL)
		return (1);
	tmp->left = cmd_info;
	argvs = convert_lst_to_array(lst);
	if (argvs == NULL)
		return (1);
	tmp->left->contents = argvs;
	return (0);
}

int	insert_pipeline(t_tree_node *root, t_deque *tokens, t_list *lst)
{
	t_tree_node	*tmp;

	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (root == NULL || (root->token_type == PIPELINE && root->right == NULL))
		return (print_syntax_token_error("|"));
	if (lst->head != NULL)
		if (insert_cmd_info(root, lst))
			return (1);
	tmp = create_tree_node(deque_front(tokens));
	if (tmp == NULL)
		return (1);
	tmp->left = root;
	root = tmp;
	deque_pop_front(tokens);
	return (0);
}

int	insert_cmd_token(t_data *data)
{
	t_tree_node	*cmd;

	cmd = NULL;
	if (data->root == NULL
		|| (data->root->token_type == PIPELINE && data->root->right == NULL))
	{
		cmd = create_tree_node(deque_front(data->tokens));
		if (cmd == NULL)
			return (1);
	}
	if (data->root == NULL)
		data->root = cmd;
	else if (data->root->token_type == PIPELINE && data->root->right == NULL)
		data->root->right = cmd;
	if (deque_front(data->tokens) == CMD || deque_front(data->tokens) == ARGV)
	{
		if (analyze_cmd_argv(data, data->tokens->front->content))
			return (1);
	}
	deque_pop_front(data->tokens);
	return (0);
}

int	insert_filename(t_tree_node *root, t_deque *tokens)
{
	t_tree_node	*file;
	char		*filename;
	char		**strs;

	file = create_tree_node(FILENAME);
	filename = ft_strdup(tokens->front->content);
	strs = (char **)malloc(sizeof(char *) * 2);
	if (!file || !filename || !strs)
	{
		if (file)
			free(file);
		if (filename)
			free(strs);
		return (1);
	}
	strs[0] = filename;
	strs[1] = NULL;
	file->contents = strs;
	root->right = file;
	deque_pop_front(tokens);
	return (0);
}

int	insert_redirection_type(t_tree_node *root, t_deque *tokens)
{
	t_tree_node	*rd_real;
	char		*rd_content;
	int			token_type;

	rd_content = tokens->front->content;
	token_type = 0;
	if (!ft_strncmp(rd_content, "<", 1))
		token_type = LESS;
	else if (!ft_strncmp(rd_content, ">", 1))
		token_type = GREAT;
	else if (!ft_strncmp(rd_content, "<<", 2))
		token_type = DLESS;
	else if (!ft_strncmp(rd_content, ">>", 2))
		token_type = DGREAT;
	rd_real = create_tree_node(token_type);
	if (rd_real == NULL)
		return (1);
	root->left = rd_real;
	deque_pop_front(tokens);
	return (0);
}

int	insert_redirection_info(t_tree_node *root, t_deque *tokens)
{
	t_tree_node	*rd_info;

	rd_info = create_tree_node(root->token_type);
	if (rd_info == NULL)
		return (1);
	root->left = rd_info;
	if (insert_redirection_type(root->left, tokens))
		return (1);
	if (insert_filename(root->left, tokens))
		return (1);
	return (0);
}

int	insert_redirection_list(t_tree_node *root, t_deque *tokens, t_data *data)
{
	t_tree_node	*rd;
	t_tree_node	*tmp;

	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (tokens->front->right->token_type != FILENAME)
		return (print_syntax_token_error(tokens->front->right->content));
	if (root == NULL || (root->token_type == PIPELINE && root->right == NULL))
	{
		if (insert_cmd_token(data))
			return (1);
	}
	tmp = root;
	while (tmp->right != NULL)
		tmp = tmp->right;
	rd = create_tree_node(tokens->front->token_type);
	if (rd == NULL)
		return (1);
	tmp->right = rd;
	if (insert_redirection_info(tmp->right, tokens))
		return (1);
	return (0);
}

int	analyze_syntax(t_data *data)
{
	int		token_type;
	int		check;

	while (!deque_empty(data->tokens))
	{
		token_type = deque_front(data->tokens);
		if (token_type == CMD || token_type == ARGV)
			check = insert_cmd_token(data);
		else if (token_type == REDIRECTION)
			check = insert_redirection_list(data->root, data->tokens, data);
		else if (token_type == PIPELINE)
			check = insert_pipeline(data->root, data->tokens, data->argv_lst);
		if (check)
			return (1);
	}
	if (data->argv_lst->head != NULL)
	{
		check = insert_cmd_token(data);
		if (check)
			return (1);
	}
	return (0);
}
