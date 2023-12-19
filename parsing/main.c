/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:59:04 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/19 16:02:56 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*parse_line(char *line)
{
	int			flag;
	t_data		*data;
	t_tree_node	*ret;

	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		exit(1);
	if (init_data(data))
		exit(1);
	if (tokenize(line, data))
		exit(1);
	flag = analyze_syntax(data);
	if (flag == 1)
		exit(1);
	else if (flag == -1)
		return (NULL);
	ret = data->root;
	free_data(data);
	return (ret);
}
