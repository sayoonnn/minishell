/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:04:50 by devpark           #+#    #+#             */
/*   Updated: 2024/01/01 21:04:51 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

char	*handle_dollar_special(char *content, size_t *idx)
{
	char	*res;

	res = NULL;
	if (content[*idx] == 0)
		res = ft_strdup("$");
	else if (content[*idx] == '$' || ft_isdigit(content[*idx]))
	{
		(*idx)++;
		res = ft_strdup("");
	}
	else if (is_quote(content[*idx]))
		res = ft_strdup("");
	else if (content[*idx] == '?')
	{
		(*idx)++;
		res = ft_itoa(g_errcode);
	}
	if (res == NULL)
		return (NULL);
	return (res);
}

char	*handle_dollar(char *cnt, t_envtree *env, size_t *idx)
{
	char		*res;
	char		*key;
	size_t		tmp_idx;
	t_envnode	*node;

	tmp_idx = ++(*idx);
	if (is_quote(cnt[tmp_idx]) || cnt[tmp_idx] == 0 || ft_isdigit(cnt[tmp_idx])
		|| cnt[tmp_idx] == '?' || cnt[tmp_idx] == '$')
		return (handle_dollar_special(cnt, idx));
	while (cnt[tmp_idx] != 0 && cnt[tmp_idx] != '$'
		&& !is_quote(cnt[tmp_idx]) && !is_bracket(cnt[tmp_idx]))
		tmp_idx++;
	key = ft_substr(cnt, *idx, tmp_idx - *idx);
	if (key == NULL)
		return (NULL);
	node = find_envnode(env->root, key);
	free(key);
	if (node != NULL)
		res = ft_strdup(node->value);
	else
		res = ft_strdup("");
	if (res == NULL)
		return (NULL);
	*idx = tmp_idx;
	return (res);
}

int	refine_content(char *content, t_envtree *env, char **refine, size_t *idx)
{
	char	*res;
	char	*value;
	size_t	s;

	s = *idx;
	value = handle_dollar(content, env, idx);
	if (value == NULL)
	{
		free(*refine);
		return (1);
	}
	res = ft_strjoin(*refine, value);
	if (res == NULL)
	{
		free(*refine);
		free(value);
		return (1);
	}
	free(*refine);
	free(value);
	*refine = res;
	return (0);
}

int	substitute_dollar(t_list *res, char *content, t_envtree *env, char **ref)
{
	size_t	idx;
	size_t	s;

	if (*ref == NULL)
		return (1);
	idx = 0;
	s = 0;
	while (content[idx])
	{
		if (content[idx] == '$')
		{
			if (ft_strjoin_in_depend(ref, content, &s, &idx))
				return (1);
			idx = s;
			if (refine_content(content, env, ref, &idx))
				return (1);
			s = idx;
			continue ;
		}
		idx++;
	}
	if (ft_strjoin_in_depend(ref, content, &s, &idx))
		return (1);
	return (remove_all_quotes(res, *ref));
}

t_list	*interprete_words(t_list *contents, t_envtree *env)
{
	t_list	*res;
	t_node	*ptr;
	char	*refined;

	res = ft_lstcreate();
	if (res == NULL)
		return (NULL);
	ptr = contents->head;
	while (ptr != NULL)
	{
		refined = ft_strdup("");
		if (substitute_dollar(res, ptr->content, env, &refined))
			return (NULL);
		ptr = ptr->next;
	}
	return (res);
}
