/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:10:15 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 23:26:42 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

void	cut_tree(t_tree_node *root)
{
	size_t	word_idx;

	word_idx = 0;
	if (root != NULL)
	{
		cut_tree(root->left);
		cut_tree(root->right);
		if (root->contents != NULL)
		{
			while (root->contents[word_idx] != NULL)
			{
				free(root->contents[word_idx]);
				word_idx++;
			}
			free(root->contents);
		}
		free(root);
	}
}

int	init_data(t_data *data)
{
	data->tokens = deque_create();
	data->argv_lst = ft_lstcreate();
	if (!(data->tokens) || !(data->argv_lst))
	{
		if (data->tokens)
			free(data->tokens);
		return (1);
	}
	data->detach = 0;
	data->cmd_flag = 0;
	data->root = 0;
	return (0);
}

void	free_data(t_data *data)
{
	if (!(data->tokens) || !(data->argv_lst) || !(data->root))
	{
		if (data->tokens)
		{
			if (!deque_empty(data->tokens))
				deque_clear(data->tokens);
			free(data->tokens);
		}
		if (data->argv_lst)
			free(data->argv_lst);
		if (data->root)
			cut_tree(data->root);
	}
	free(data);
}
