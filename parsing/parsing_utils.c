/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:02:00 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/02 12:40:34 by devpark          ###   ########.fr       */
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
	return (ch == '<' || ch == '>' || ch == '|');
}

int	is_bracket(char ch)
{
	return (ch == '(' || ch == ')' || ch == '{' || ch == '}'\
			|| ch == '[' || ch == ']');
}
