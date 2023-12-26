/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:00:26 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 17:46:01 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	free_new_argv(char *argv)
{
	free(argv);
	return (1);
}

int	link_argv(t_parsing *parsing, char *argv)
{
	char	*res;
	t_list	*new;

	if (argv == NULL)
		return (1);
	if (ft_strlen(argv) == 0)
		free(argv);
	else if (parsing->word_lst->head == 0 || parsing->detach == 0)
	{
		new = ft_lstnew(argv);
		if (new == NULL)
			return (free_new_argv(argv));
		ft_lstadd_back(parsing->word_lst, new);
		parsing->detach = 1;
	}
	else if (parsing->detach)
	{
		res = ft_strjoin(parsing->word_lst->tail->content, argv);
		if (res == NULL)
			return (free_new_argv(argv));
		free(parsing->word_lst->tail->content);
		free(argv);
		parsing->word_lst->tail->content = res;
	}
	return (0);
}

int	link_argv_to_lst(t_parsing *parsing, char **strs, char *value)
{
	char	*dup;
	size_t	word_idx;

	word_idx = 0;
	parsing->detach = !(is_white(value[0]));
	while (strs[word_idx] != NULL)
	{
		dup = ft_strdup(strs[word_idx]);
		if (dup == NULL)
			return (free_perfectly_split(strs));
		if (link_argv(parsing, dup))
		{
			free(dup);
			return (free_perfectly_split(strs));
		}
		parsing->detach = 0;
		word_idx++;
	}
	parsing->detach = !(is_white(value[ft_strlen(value) - 1]));
	free_perfectly_split(strs);
	return (0);
}

int	process_special_dollar(t_parsing *parsing, char *word, size_t *idx)
{
	char	*res;

	res = NULL;
	if (word[*idx] == 0)
		res = make_word(word, idx, 1);
	else if (word[(*idx)++] == '?')
		res = ft_itoa(err_code);
	if (res == NULL)
		return (1);
	if (link_argv(parsing, res))
		return (free_new_argv(res));
	return (0);
}

int	process_dollar_in_word(t_parsing *parsing, char *word, size_t *idx)
{
	size_t	tmp_idx;
	char	*key;
	char	*value;
	char	**strs;

	if (is_quote(word[++(*idx)]))
		return (0);
	if (word[*idx] == 0)
		return (process_special_dollar(parsing, word, idx));
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
		return (link_argv_to_lst(parsing, strs, value));
	}
	return (0);
}

int	check_word_in_syntax(t_parsing *parsing, char *word, size_t *idx)
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
			if (link_argv(parsing, sliced))
				return (1);
			if (process_dollar_in_word(parsing, word, idx))
				return (1);
			tmp_idx = *idx;
			continue ;
		}
		tmp_idx++;
	}
	sliced = make_word(word, &tmp_idx, (tmp_idx - *idx));
	(*idx) = tmp_idx;
	if (link_argv(parsing, sliced))
		return (1);
	return (0);
}

int	process_dollar_in_quotes(t_parsing *parsing, char *word, size_t *idx)
{
	size_t	tmp_idx;
	char	*key;
	char	*value;

	if (word[*idx + 1] == 0)
		return (process_special_dollar(parsing, word, idx));
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
		if (link_argv(parsing, ft_strdup(value)))
			return (1);
	return (0);
}

int	check_rquote_in_syntax(t_parsing *parsing, char *word, size_t *idx)
{
	char	quote;
	size_t	tmp_idx;

	quote = word[(*idx)++];
	tmp_idx = *idx;
	while (word[tmp_idx] != quote && word[tmp_idx] != 0)
	{
		if (quote == '"' && word[tmp_idx] == '$')
		{
			if (link_argv(parsing, make_word(word, &tmp_idx, tmp_idx - *idx)))
				return (1);
			(*idx) = tmp_idx;
			if (process_dollar_in_quotes(parsing, word, idx))
				return (1);
			tmp_idx = *idx;
			continue ;
		}
		tmp_idx++;
	}
	if (link_argv(parsing, make_word(word, &tmp_idx, tmp_idx - *idx)))
		return (1);
	(*idx) = tmp_idx + is_quote(word[tmp_idx]);
	return (0);
}

int	substitute_word(t_parsing *parsing, char *content)
{
	size_t	idx;

	idx = 0;
	while (content[idx] != 0)
	{
		if (is_quote(content[idx]))
		{
			if (check_rquote_in_syntax(parsing, content, &idx))
				return (1);
			continue ;
		}
		if (check_word_in_syntax(parsing, content, &idx))
			return (1);
	}
	return (0);
}

char	**substitute_words(t_parsing *parsing, t_list *contents)
{
	t_node			*ptr;
	char			**words;
	unsigned int	cnt;
	unsigned int	idx;

	ptr = contents->head;
	while (ptr != NULL)
	{
		if (substitute_word(parsing, ptr->content))
			return (NULL);
		ptr = ptr->next;
	}
	cnt = count_words(parsing->word_lst);
	words = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (words == NULL)
		return (NULL);
	ptr = parsing->word_lst->head;
	idx = 0;
	while (ptr != NULL)
	{
		words[idx++] = ptr->content;
		ptr = ptr->next;
	}
	words[idx] = NULL;
	return (words);
}
