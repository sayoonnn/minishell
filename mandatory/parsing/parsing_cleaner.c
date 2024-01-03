/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:34:22 by devpark           #+#    #+#             */
/*   Updated: 2023/12/26 16:55:14 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

void	cut_tree(t_tree_node *root)
{
	if (root != NULL)
	{
		cut_tree(root->left);
		cut_tree(root->right);
		if (root->contents != NULL)
		{
			ft_lstclear(root->contents);
			free(root->contents);
		}
		free(root);
	}
}

void	clean_parsing_tools(t_parsing *parsing)
{
	deque_clear(parsing->tokens);
	cut_tree(parsing->root);
	parsing->root = NULL;
}

void	free_parsing(t_parsing *parsing)
{
	if (parsing->tokens || parsing->root)
	{
		if (parsing->tokens)
		{
			if (!deque_empty(parsing->tokens))
				deque_clear(parsing->tokens);
			free(parsing->tokens);
		}
		if (parsing->root)
			cut_tree(parsing->root);
	}
}
