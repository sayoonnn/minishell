/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:02:00 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/03 17:54:37 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"
#include "libft.h"

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

int	is_operator(char ch)
{
	return (ch == '<' || ch == '>' || ch == '|' || ch == '&');
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
