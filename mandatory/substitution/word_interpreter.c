/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_interpreter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:04:50 by devpark           #+#    #+#             */
/*   Updated: 2024/01/03 15:00:59 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution.h"

char	*handle_dollar_special(char *content, size_t *idx, char *quote)
{
	char	*res;

	res = NULL;
	if (content[*idx] == '?')
	{
		(*idx)++;
		res = ft_itoa(g_errcode);
	}
	else if (ft_isdigit(content[*idx]))
	{
		(*idx)++;
		res = ft_strdup("");
	}
	else if (is_quote(content[*idx]))
	{
		if (*quote)
			res = ft_strdup("$");
		else
			res = ft_strdup("");
	}
	else if (content[*idx] != '_' && !ft_isalpha(content[*idx]))
		res = ft_strdup("$");
	if (res == NULL)
		return (NULL);
	return (res);
}

char	*handle_dollar(char *cont, t_envtree *env, size_t *idx, char *quote)
{
	char		*res;
	size_t		tmp;
	char		*key;
	t_envnode	*node;

	res = NULL;
	tmp = ++(*idx);
	if (cont[tmp] == '?' || is_quote(cont[tmp]) || ft_isdigit(cont[tmp])
		|| (cont[tmp] != '_' && !ft_isalpha(cont[tmp])))
		return (handle_dollar_special(cont, idx, quote));
	while (cont[tmp] == '_' || ft_isalnum(cont[tmp]))
		tmp++;
	key = ft_substr(cont, *idx, tmp - *idx);
	node = find_envnode(env->root, key);
	free(key);
	if (node != NULL && node->value != NULL)
		res = ft_strdup(node->value);
	else
		res = ft_strdup("");
	*idx = tmp;
	return (res);
}

int	substitute_dollar(char *content, t_envtree *env, char **ref)
{
	size_t	start;
	size_t	idx;
	char	quote;
	char	*value;

	start = 0;
	idx = 0;
	quote = 0;
	while (content[idx])
	{
		update_quote_info(content[idx], &quote);
		if (content[idx] == '$' && quote != '\'')
		{
			if (ft_strjoin_in_depend(ref, content, &start, &idx))
				return (1);
			start = idx;
			value = handle_dollar(content, env, &idx, &quote);
			if (ft_strjoin_with_value(ref, value))
				return (1);
			start = idx;
			continue ;
		}
		idx++;
	}
	return (ft_strjoin_in_depend(ref, content, &start, &idx));
}

int	substitute_dollar_heredoc(char *content, t_envtree *env, char **ref)
{
	size_t	start;
	size_t	idx;
	char	quote;
	char	*value;

	start = 0;
	idx = 0;
	quote = 0;
	while (content[idx])
	{
		if (content[idx] == '$')
		{
			if (ft_strjoin_in_depend(ref, content, &start, &idx))
				return (1);
			start = idx;
			value = handle_dollar(content, env, &idx, &quote);
			if (ft_strjoin_with_value(ref, value))
				return (1);
			start = idx;
			continue ;
		}
		idx++;
	}
	return (ft_strjoin_in_depend(ref, content, &start, &idx));
}

t_list	*interprete_words(t_list *contents, t_envtree *env)
{
	t_list	*res;
	t_node	*ptr;
	t_list	*tmp;

	res = ft_lstcreate();
	if (res == NULL)
		exit(1);
	ptr = contents->head;
	while (ptr != NULL)
	{
		tmp = expansion(ptr->content, env);
		sum_lst(res, tmp);
		ptr = ptr->next;
		free(tmp);
	}
	return (res);
}
