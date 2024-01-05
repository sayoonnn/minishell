/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleaner_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:34:22 by devpark           #+#    #+#             */
/*   Updated: 2024/01/05 14:07:22 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

void	cut_tree(t_tree_node *root)
{
	if (root == NULL)
		return ;
	if (root->token_type == SUBSHELL)
		cut_tree(root->mid);
	cut_tree(root->left);
	cut_tree(root->right);
	if (root->contents != NULL)
	{
		while (root->contents->head != NULL)
			ft_lstclear(root->contents);
		free(root->contents);
	}
	free(root);
}

void	clean_parsing_tools(t_parsing *parsing)
{
	deque_clear(parsing->tokens);
	cut_tree(parsing->root);
	parsing->root = NULL;
	parsing->subsh_cnt = 0;
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
