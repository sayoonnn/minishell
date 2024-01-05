/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:02:00 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/05 14:26:21 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"
#include "libft_bonus.h"

int	is_white(char ch)
{
	return (ch == ' ' || (ch >= 9 && ch <= 13));
}

int	is_quote(char ch)
{
	return (ch == '\'' || ch == '"');
}

int	is_parenthesis(char ch)
{
	return (ch == '(' || ch == ')');
}

int	is_operator(char *cmd, size_t idx)
{
	if (cmd[idx] == '<' || cmd[idx] == '>' || cmd[idx] == '|')
		return (1);
	if (!ft_strncmp(cmd + idx, "&&", 2))
		return (1);
	return (0);
}

int	is_brack(char ch)
{
	if (ch == '(' || ch == ')')
		return (1);
	if (ch == '{' || ch == '}')
		return (1);
	if (ch == '[' || ch == ']')
		return (1);
	return (0);
}
