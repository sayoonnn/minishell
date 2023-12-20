/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:59:04 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/20 13:51:24 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

void	func()
{
	system("leaks -q test");
}

void	traverse_parse_tree(t_tree_node *root)
{
	if (root != NULL)
	{
		traverse_parse_tree(root->left);
		printf("%d\n", root->token_type);
		traverse_parse_tree(root->right);
	}
}

int	main(void)
{
	char	*cmd = "ls -l -a >>a<<b>c| grep \"\" | cat <x>>y";
	t_data	*data;

	atexit(func);
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	if (init_data(data))
		return (1);
	if (tokenize(cmd, data))
	{
		free_data(data);
		return (1);
	}
	if (analyze_syntax(data))
	{
		free_data(data);
		return (1);
	}
	printf("Syntax Clear\n");
	// traverse_parse_tree(data->root);
	if (data->root->token_type == PIPELINE)
		printf("root : PIPELINE");
	else if (data->root->token_type == CMD)
		printf("root : CMD");
	free_data(data);
	return (0);
}
