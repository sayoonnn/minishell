/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:00:26 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/18 19:17:43 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	process_dollar_in_word(t_data *data, char *word, size_t *idx)
{
	size_t	tmp_idx;
	char	*key;
	char	*value;
	char	**strs;

	if (is_quote(word[++(*idx)]))
		return (0);
	if (word[*idx] == 0)
		return (process_special_dollar(data, word, idx));
	tmp_idx = (*idx);
	while (word[tmp_idx] != 0 && word[tmp_idx] != '$'
		&& !is_quote(word[tmp_idx]))
		tmp_idx++;
	key = make_word(word, &tmp_idx, tmp_idx - (*idx));
	if (key == NULL)
		return (1);
	value = getenv(key);
	free(key);
	(*idx) = tmp_idx;
	if (value != NULL)
	{
		strs = ft_split(value);
		return (link_argv_to_lst(data, strs, value));
	}
	return (0);
}

int	check_word_in_syntax(t_data *data, char *word, size_t *idx)
{
	size_t	tmp_idx;
	char	*sliced;

	tmp_idx = *idx;
	while (word[tmp_idx] != 0 && !is_quote(word[tmp_idx]))
	{
		if (word[tmp_idx] == '$')
		{
			sliced = make_word(word, &tmp_idx, (tmp_idx - *idx));
			(*idx) = tmp_idx;
			if (link_argv(data, sliced))
				return (1);
			if (process_dollar_in_word(data, word, idx))
				return (1);
			tmp_idx = *idx;
			continue ;
		}
		tmp_idx++;
	}
	sliced = make_word(word, &tmp_idx, (tmp_idx - *idx));
	(*idx) = tmp_idx;
	if (link_argv(data, sliced))
		return (1);
	return (0);
}

int	process_dollar_in_quotes(t_data *data, char *word, size_t *idx)
{
	size_t	tmp_idx;
	char	*key;
	char	*value;

	if (word[*idx + 1] == 0)
		return (process_special_dollar(data, word, idx));
	tmp_idx = ++(*idx);
	while (word[tmp_idx] != '"' && word[tmp_idx] != 0
		&& !is_white(word[tmp_idx]) && word[tmp_idx] != '$')
		tmp_idx++;
	key = make_word(word, &tmp_idx, (tmp_idx - *idx));
	if (key == NULL)
		return (1);
	value = getenv(key);
	free(key);
	*idx = tmp_idx;
	if (value != NULL)
		if (link_argv(data, ft_strdup(value)))
			return (1);
	return (0);
}

int	check_rquote_in_syntax(t_data *data, char *word, size_t *idx)
{
	char	quote;
	size_t	tmp_idx;

	quote = word[(*idx)++];
	tmp_idx = *idx;
	while (word[tmp_idx] != quote && word[tmp_idx] != 0)
	{
		if (quote == '"' && word[tmp_idx] == '$')
		{
			if (link_argv(data, make_word(word, &tmp_idx, tmp_idx - *idx)))
				return (1);
			(*idx) = tmp_idx;
			if (process_dollar_in_quotes(data, word, idx))
				return (1);
			tmp_idx = *idx;
			continue ;
		}
		tmp_idx++;
	}
	if (word[tmp_idx] == 0)
		return (print_syntax_unmatched_error(quote));
	if (link_argv(data, make_word(word, &tmp_idx, tmp_idx - *idx)))
		return (1);
	(*idx) = tmp_idx + is_quote(word[tmp_idx]);
	return (0);
}

int	analyze_cmd_argv(t_data *data, char *word)
{
	int		detach;
	size_t	idx;

	detach = 0;
	idx = 0;
	while (word[idx] != 0)
	{
		if (is_quote(word[idx]))
		{
			if (check_rquote_in_syntax(data, word, &idx))
				return (1);
			continue ;
		}
		if (check_word_in_syntax(data, word, &idx))
			return (1);
	}
	return (0);
}
