/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:31:08 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 17:28:07 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

t_tree_node	*parse_line(char *line, t_parsing *parsing)
{
	int			flag;
	t_tree_node	*ret;

	if (*line == 0)
		return (NULL);
	if (tokenize(line, parsing))
		exit(1);
	flag = analyze_syntax(parsing);
	if (flag == 1)
		return (NULL);
	ret = parsing->root;
	parsing->detach = 0;
	return (ret);
}
