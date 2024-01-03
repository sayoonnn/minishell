/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 22:19:34 by devpark           #+#    #+#             */
/*   Updated: 2024/01/01 22:27:30 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"
#include "errors.h"

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

int	insert_cmd_info_token(t_tree_node **root, t_parsing *parsing)
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
	parsing->cmd_info_ptr = cmd_info;
	return (0);
}

int	connect_cmd_argv_content(t_tree_node **root, t_parsing *parsing)
{
	t_node	*new;
	char	*content;

	if (*root == NULL
		|| ((*root)->token_type == PIPE && (*root)->right == NULL))
	{
		if (insert_cmd_info_token(root, parsing))
			return (1);
	}
	content = ft_strdup(parsing->tokens->front->content);
	new = ft_lstnew(content);
	if (content == NULL || new == NULL)
	{
		if (content)
			free(content);
		return (1);
	}
	ft_lstadd_back(parsing->cmd_info_ptr->contents, new);
	deque_pop_front(parsing->tokens);
	return (0);
}
