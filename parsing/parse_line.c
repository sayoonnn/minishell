/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:31:08 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/19 16:31:17 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tree_node	*parse_line(char *line)
{
	int			flag;
	t_data		*data;
	t_tree_node	*ret;

	if (*line == 0)
		return (NULL);
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		exit(1);
	if (init_data(data))
		exit(1);
	if (tokenize(line, data))
		exit(1);
	flag = analyze_syntax(data);
	if (flag == 1)
	{
		ret = data->root;
		free_data(data);
		return (NULL);
	}
	ret = data->root;
	free_data(data);
	return (ret);
}
