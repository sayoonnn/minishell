/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 20:26:18 by devpark           #+#    #+#             */
/*   Updated: 2024/01/03 14:06:13 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

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
