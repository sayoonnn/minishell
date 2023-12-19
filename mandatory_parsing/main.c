/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:59:04 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 23:10:48 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

void	func()
{
	system("leaks -q a.out");
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
	char	*cmd = "ls -l -a >>a <<b>c | grep \"\" | cat <x >> y";
	t_data	*data;

	atexit(func);
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	if (init_data(data))
		return (1);
	if (tokenize(cmd, data) || analyze_syntax(data))
	{
		free_data(data);
		return (1);
	}
	traverse_parse_tree(data->root);
	free_data(data);
	return (0);
}
