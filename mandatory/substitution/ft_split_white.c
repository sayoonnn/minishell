/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_white.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 16:33:34 by devpark           #+#    #+#             */
/*   Updated: 2023/12/29 21:48:56 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

static void	check_quote_flag(char const *s, size_t *idx, int *flag, char *quote)
{
	if (is_quote(s[*idx]) && !(*flag))
	{
		*flag = 1;
		*quote = s[*idx];
	}
	else if (is_quote(s[*idx]) && *flag && s[*idx] == *quote)
		*flag = 0;
}

static int	count_words(char const *s)
{
	size_t	idx;
	int		cnt;
	int		word_flag;
	int		quote_flag;
	char	quote;

	idx = 0;
	word_flag = 0;
	quote_flag = 0;
	cnt = 0;
	while (s[idx] != 0)
	{
		check_quote_flag(s, &idx, &quote_flag, &quote);
		if (!is_white(s[idx]) && !word_flag)
		{
			word_flag = 1;
			cnt++;
		}
		else if (is_white(s[idx]) && word_flag && !quote_flag)
			word_flag = 0;
		idx++;
	}
	return (cnt);
}

static void	find_word_area(char const *s, size_t *start, size_t *end)
{
	int		quote_flag;
	char	quote;

	quote_flag = 0;
	while (*start < *end)
		++(*start);
	while (is_white(s[*start]))
		++(*start);
	*end = *start;
	while (s[*end] != 0
		&& (!is_white(s[*end]) || (is_white(s[*end]) && quote_flag)))
	{
		if (is_quote(s[*end]) && !quote_flag)
		{
			quote_flag = 1;
			quote = s[*end];
		}
		else if (is_quote(s[*end]) && quote_flag && s[*end] == quote)
			quote_flag = 0;
		++(*end);
	}
}

char	**ft_split_white(char const *s)
{
	size_t	s_idx;
	size_t	e_idx;
	int		word_idx;
	int		word_cnt;
	char	**words;

	word_idx = 0;
	s_idx = 0;
	e_idx = 0;
	word_cnt = count_words(s);
	words = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (words == NULL)
		return (NULL);
	while (word_idx < word_cnt)
	{
		find_word_area(s, &s_idx, &e_idx);
		words[word_idx] = ft_substr(s, s_idx, e_idx - s_idx);
		if (words[word_idx++] == NULL)
		{
			free_perfectly_split(words);
			return (NULL);
		}
	}
	words[word_idx] = NULL;
	return (words);
}
