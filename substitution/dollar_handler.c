/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 21:13:22 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 21:13:41 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_special_dollar(t_parsing *parsing, char *word, size_t *idx)
{
	char	*res;

	res = NULL;
	if (word[*idx] == 0 || is_quote(word[*idx]) || is_white(word[*idx]))
		res = make_word(word, idx, 1);
	else if (word[(*idx)++] == '?')
		res = ft_itoa(err_code);
	if (res == NULL)
		return (1);
	if (link_argv(parsing, res))
		return (1);
	*idx += (word[*idx] == '?');
	return (0);
}

int	handle_dollar_in_qts(t_parsing *ps, t_envtree *env, char *word, size_t *idx)
{
	size_t		tmp_idx;
	t_envnode	*envnode;
	char		*key;

	if (word[++(*idx)] == '?' || is_white(word[*idx]) || is_quote(word[*idx]))
		return (handle_special_dollar(ps, word, idx));
	tmp_idx = (*idx);
	while (word[tmp_idx] != '"'
		&& !is_white(word[tmp_idx]) && !is_quote(word[tmp_idx]))
		tmp_idx++;
	key = make_word(word, &tmp_idx, tmp_idx - (*idx));
	if (key == NULL)
		return (1);
	(*idx) = tmp_idx;
	envnode = find_envnode(env->root, key);
	free(key);
	if (envnode != NULL)
		if (link_argv(ps, ft_strdup(envnode->value)))
			return (1);
	return (0);
}

int	handle_dollar_in_wd(t_parsing *ps, t_envtree *env, char *word, size_t *idx)
{
	size_t		tmp_idx;
	char		*key;
	t_envnode	*envnode;
	char		**strs;

	if (is_quote(word[++(*idx)]))
		return (0);
	if (word[*idx] == 0)
		return (handle_special_dollar(ps, word, idx));
	tmp_idx = (*idx);
	while (word[tmp_idx] != 0 && word[tmp_idx] != '$'
		&& !is_quote(word[tmp_idx]))
		tmp_idx++;
	key = make_word(word, &tmp_idx, tmp_idx - (*idx));
	if (key == NULL)
		return (1);
	envnode = find_envnode(env->root, key);
	free(key);
	(*idx) = tmp_idx;
	if (envnode != NULL)
	{
		strs = ft_split(envnode->value);
		return (link_argv_to_word_lst(ps, strs, envnode->value));
	}
	return (0);
}

int	handle_wd(t_parsing *ps, t_envtree *env, char *word, size_t *idx)
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
			if (link_argv(ps, sliced))
				return (1);
			if (handle_dollar_in_wd(ps, env, word, idx))
				return (1);
			tmp_idx = *idx;
			continue ;
		}
		tmp_idx++;
	}
	sliced = make_word(word, &tmp_idx, tmp_idx - *idx);
	(*idx) = tmp_idx;
	return (link_argv(ps, sliced));
}

int	handle_word_with_qts(t_parsing *ps, t_envtree *env, char *word, size_t *idx)
{
	size_t	tmp_idx;
	char	quote;

	quote = word[(*idx)++];
	tmp_idx = *idx;
	while (word[tmp_idx] != quote)
	{
		if (quote == '"' && word[tmp_idx] == '$')
		{
			if (link_argv(ps, make_word(word, &tmp_idx, tmp_idx - *idx)))
				return (1);
			(*idx) = tmp_idx;
			if (handle_dollar_in_qts(ps, env, word, idx))
				return (1);
			tmp_idx = *idx;
			continue ;
		}
		tmp_idx++;
	}
	if (link_argv(ps, make_word(word, &tmp_idx, tmp_idx - *idx)))
		return (1);
	(*idx) = tmp_idx + 1;
	return (0);
}
