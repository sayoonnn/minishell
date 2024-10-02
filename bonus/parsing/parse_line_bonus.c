/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:31:08 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 15:11:21 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

int	parse_line(char *line, t_parsing *parsing)
{
	int	flag;

	if (*line == 0)
	{
		free(line);
		return (false);
	}
	if (tokenize(line, parsing))
		exit(1);
	flag = analyze_syntax(&parsing->root, parsing);
	if (flag == 1)
		exit(1);
	if (flag == 258)
	{
		clean_parsing_tools(parsing);
		free(line);
		return (false);
	}
	return (true);
}
