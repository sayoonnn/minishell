/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 04:01:01 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/16 19:55:13 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_setchar(char ch, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
		if (ch == set[i++])
			return (1);
	return (0);
}

void	trim_back(char const *s1, char const *set, size_t *end)
{
	while (*end > 0)
	{
		if (!is_setchar(s1[*end - 1], set))
			break ;
		(*end)--;
	}
}

void	trim_front(char const *s1, char const *set, size_t *start)
{
	while (s1[*start] != 0)
	{
		if (!is_setchar(s1[*start], set))
			break ;
		(*start)++;
	}
}

void	find_set_ch(char const *s1, char const *set, size_t *start, size_t *end)
{
	trim_front(s1, set, start);
	if (*start < *end)
		trim_back(s1, set, end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	size_t	start_idx;
	size_t	end_idx;
	size_t	new_str_len;
	size_t	new_idx;

	if (s1 == 0 || set == 0)
		return (0);
	start_idx = 0;
	end_idx = ft_strlen(s1);
	find_set_ch(s1, set, &start_idx, &end_idx);
	if (start_idx < end_idx)
		new_str_len = end_idx - start_idx;
	else
		new_str_len = 0;
	new_str = (char *)malloc(sizeof(char) * (new_str_len + 1));
	if (new_str == NULL)
		return (NULL);
	new_idx = 0;
	while (start_idx < end_idx)
		new_str[new_idx++] = s1[start_idx++];
	new_str[new_idx] = 0;
	return (new_str);
}
