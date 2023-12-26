/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_analyzer_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:55:58 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 16:32:04 by devpark          ###   ########.fr       */
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
	else if (parsing->argv_lst->head == 0 || parsing->detach == 0)
	{
		new = ft_lstnew(argv);
		if (new == NULL)
			return (free_new_argv(argv));
		ft_lstadd_back(parsing->argv_lst, new);
		parsing->detach = 1;
	}
	else if (parsing->detach)
	{
		res = ft_strjoin(parsing->argv_lst->tail->content, argv);
		if (res == NULL)
			return (free_new_argv(argv));
		free(parsing->argv_lst->tail->content);
		free(argv);
		parsing->argv_lst->tail->content = res;
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
	// else if (word[(*idx)++] == '?')
	// 	res = itoa(0);
	if (res == NULL)
		return (1);
	if (link_argv(parsing, res))
		return (free_new_argv(res));
	return (0);
}
