/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:02:00 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 21:02:19 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	is_white(char ch)
{
	return (ch == ' ' || (ch >= 9 && ch <= 13));
}

int	is_quote(char ch)
{
	return (ch == '\'' || ch == '"');
}

int	is_operator(char ch)
{
	if (ch == '<' || ch == '>' || ch == '|')
		return (1);
	return (0);
}

int	free_perfectly_split(char **strs)
{
	size_t	idx;

	idx = 0;
	while (strs[idx] != NULL)
	{
		free(strs[idx]);
		idx++;
	}
	free(strs);
	return (1);
}
