/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_interpreter_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 21:04:50 by devpark           #+#    #+#             */
/*   Updated: 2024/01/05 13:49:05 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "substitution_bonus.h"

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

int	ft_strjoin_with_value(char **refine, char *value)
{
	char	*res;

	if (value == NULL)
		return (1);
	res = ft_strjoin(*refine, value);
	free(*refine);
	free(value);
	if (res == NULL)
		return (1);
	*refine = res;
	return (0);
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

static void	sum_lst(t_list *dst, t_list *src)
{
	if (src->head == NULL && src->tail == NULL)
		return ;
	ft_lstadd_back(dst, src->head);
	while (dst->tail->next != NULL)
		dst->tail = dst->tail->next;
	free(src);
}

static t_list	*sum_lst_middle(t_list *dst_lst, t_node *dst, t_list *src)
{
	t_list	*tmp;
	t_node	*node;

	tmp = ft_lstcreate();
	if (!tmp)
		exit(1);
	node = dst_lst->head;
	while (node != dst)
	{
		ft_lstadd_back(tmp, node);
		node = node->next;
	}
	if (tmp->tail == NULL)
	{
		tmp->head = src->head;
		tmp->tail = src->head;
	}
	else
		tmp->tail->next = src->head;
	src->tail->next = node->next;
	while (tmp->tail->next != NULL)
		tmp->tail = tmp->tail->next;
	return (tmp);
}

static void	wildcard_change(char *str)
{
	while (*str)
	{
		if (*str == 5)
			*str = '*';
		str++;
	}
}

static void	expand_wilds(t_list *res)
{
	t_node	*ptr;
	t_node	*tmp;
	t_list	*replaced;

	ptr = res->head;
	while (ptr != NULL)
	{
		if (ft_strchr(ptr->content, 5))
		{
			replaced = make_pattern_match_list(ptr->content);
			if (replaced->head)
			{
				tmp = ptr->next;
				sum_lst_middle(res, ptr, replaced);
				ft_lstdelone(ptr);
				ptr = tmp;
			}
			else
				wildcard_change(ptr->content);
		}
		else
			ptr = ptr->next;
	}
}

t_list	*interprete_words(t_list *contents, t_envtree *env)
{
	t_list	*res;
	t_node	*ptr;

	res = ft_lstcreate();
	if (res == NULL)
		return (NULL);
	ptr = contents->head;
	while (ptr != NULL)
	{
		sum_lst(res, expansion(ptr->content, env));
		ptr = ptr->next;
	}
	expand_wilds(res);
	return (res);
}
