/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 22:02:00 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 11:08:00 by devpark          ###   ########.fr       */
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

char	*make_word(char *cmd, size_t *idx, size_t len)
{
	char	*res;
	size_t	i;

	if (cmd == NULL)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = cmd[*idx - (len - i)];
		i++;
	}
	res[i] = 0;
	return (res);
}
