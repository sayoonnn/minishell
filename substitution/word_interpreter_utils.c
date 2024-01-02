/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_interpreter_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 21:15:15 by devpark           #+#    #+#             */
/*   Updated: 2024/01/02 12:43:02 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

void	free_perfectly_split(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
}

int	ft_strjoin_in_depend(char **s1, char *content, size_t *s, size_t *idx)
{
	char	*res;
	char	*tmp;

	tmp = ft_substr(content, *s, (*idx - *s));
	if (tmp == NULL)
	{
		free(*s1);
		return (1);
	}
	res = ft_strjoin(*s1, tmp);
	if (res == NULL)
	{
		free(*s1);
		free(tmp);
		return (1);
	}
	free(*s1);
	free(tmp);
	*s1 = res;
	return (0);
}
