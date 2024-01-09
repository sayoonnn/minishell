/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:26:18 by devpark           #+#    #+#             */
/*   Updated: 2024/01/05 13:48:58 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution_bonus.h"

int	cut_string_in_quotes(char **res, char *str, size_t *start, size_t *end)
{
	char	quote;

	if (ft_strjoin_in_depend(res, str, start, end))
		return (1);
	quote = str[*end];
	*start = ++(*end);
	while (str[*end] != quote)
		(*end)++;
	if (ft_strjoin_in_depend(res, str, start, end))
		return (1);
	*start = ++(*end);
	return (0);
}

char	*remove_quote(char *str)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	end = 0;
	res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	while (str[end] != 0)
	{
		if (is_quote(str[end]))
		{
			if (cut_string_in_quotes(&res, str, &start, &end))
				return (NULL);
			continue ;
		}
		end++;
	}
	if (ft_strjoin_in_depend(&res, str, &start, &end))
		return (NULL);
	return (res);
}

void	trim_quote(t_list *ret, char *str, int in_quote, int *is_wild)
{
	char	*tmp;
	int		is_quoted;

	is_quoted = false;
	if (is_quote(*str) && in_quote)
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 2);
		is_quoted = true;
	}
	else
	{
		tmp = ft_strdup(str);
		if (is_there_wild(str) && !in_quote)
			*is_wild = true;
	}
	if (is_there_white(tmp) && !is_quoted)
		split_n_add(ret, tmp);
	else
	{
		if (ft_lstsize(ret) != 0 && ret->tail->content == NULL)
			ft_lstadd_back(ret, ft_lstnew(tmp));
		else
			join_str_to_lastnode(ret, tmp);
	}
}
