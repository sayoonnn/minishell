/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:31:08 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/24 01:37:46 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	parse_line(char *line, t_parsing *parsing)
{
	int	flag;

	if (*line == 0)
		return (false);
	if (tokenize(line, parsing))
		exit(1);
	flag = analyze_syntax(&parsing->root, parsing);
	if (flag == 1)
		exit(1);
	if (flag == 258)
	{
		clean_parsing_tools(parsing);
		return (false);
	}
	return (true);
}
