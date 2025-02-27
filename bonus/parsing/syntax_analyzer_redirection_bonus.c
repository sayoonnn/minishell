/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer_redirection_bonus.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 17:11:56 by devpark           #+#    #+#             */
/*   Updated: 2024/01/05 12:07:42 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	insert_filename(t_tree_node **root, t_deque *tokens)
{
	t_tree_node	*file;
	t_node		*content;
	char		*tmp;

	content = NULL;
	file = create_tree_node(FILENAME);
	if (file == NULL)
		return (1);
	file->contents = ft_lstcreate();
	tmp = ft_strdup(tokens->front->content);
	if (!tmp)
		exit(1);
	content = ft_lstnew(tmp);
	if (file->contents == NULL || content == NULL)
	{
		if (file->contents)
			free(file->contents);
		free(file);
		return (1);
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
	t_tree_node	*rd_list;
	t_tree_node	*rd_info;
	t_tree_node	*tmp;

	tmp = *root;
	while (tmp->right != NULL)
		tmp = tmp->right;
	rd_list = create_tree_node(REDIRECTION_LIST);
	if (rd_list == NULL)
		return (1);
	tmp->right = rd_list;
	rd_info = create_tree_node(REDIRECTION_INFO);
	if (rd_info == NULL)
		return (1);
	tmp->right->left = rd_info;
	if (insert_redirection_type(&tmp->right->left, tokens))
		return (1);
	if (insert_filename(&tmp->right->left, tokens))
		return (1);
	return (0);
}

int	insert_cmd_info_token(t_tree_node **root, t_parsing *ps)
{
	t_tree_node	*cmd;
	t_tree_node	*cmd_info;

	cmd = create_tree_node(CMD);
	if (cmd == NULL)
		return (1);
	if (*root == NULL)
		*root = cmd;
	if (((*root)->token_type == PIPE || ((*root)->token_type == AND \
	|| (*root)->token_type == OR)) && (*root)->right == NULL)
		(*root)->right = cmd;
	if ((((*root)->token_type == AND || (*root)->token_type == OR)
			&& (*root)->right->token_type == PIPE
			&& (*root)->right->right == NULL))
		(*root)->right->right = cmd;
	cmd_info = create_tree_node(CMD_INFO);
	if (cmd_info == NULL)
		return (1);
	cmd->left = cmd_info;
	cmd_info->contents = ft_lstcreate();
	if (cmd_info->contents == NULL)
		return (1);
	ps->cmd_info_ptr = cmd_info;
	return (0);
}

int	insert_rd_list(t_tree_node **root, t_deque *tokens, t_parsing *ps)
{
	if (tokens->front->right == NULL)
		return (print_syntax_token_error("newline"));
	if (tokens->front->right->token_type != FILENAME)
		return (print_syntax_token_error(tokens->front->right->content));
	if (*root == NULL
		|| ((*root)->token_type == PIPE && (*root)->right == NULL)
		|| ((*root)->token_type == AND && (*root)->token_type == OR
			&& (*root)->right == NULL)
		|| ((*root)->token_type == AND && (*root)->token_type == OR
			&& (*root)->right->token_type == PIPE
			&& (*root)->right->right == NULL))
		if (insert_cmd_info_token(root, ps))
			return (1);
	if (insert_redirection_info(root, tokens))
		return (1);
	return (0);
}
