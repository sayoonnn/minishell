/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_analyzer_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 16:55:58 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/19 14:53:00 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	free_new_argv(char *argv)
{
	free(argv);
	return (1);
}

int	link_argv(t_data *data, char *argv)
{
	char	*res;
	t_argv	*new;

	if (argv == NULL)
		return (1);
	if (ft_strlen(argv) == 0)
		free(argv);
	else if (data->argv_lst->head == 0 || data->detach == 0)
	{
		new = ft_lstnew(argv);
		if (new == NULL)
			return (free_new_argv(argv));
		ft_lstadd_back(data->argv_lst, new);
		data->detach = 1;
	}
	else if (data->detach)
	{
		res = ft_strjoin(data->argv_lst->tail->content, argv);
		if (res == NULL)
			return (free_new_argv(argv));
		free(data->argv_lst->tail->content);
		free(argv);
		data->argv_lst->tail->content = res;
	}
	return (0);
}

int	link_argv_to_lst(t_data *data, char **strs, char *value)
{
	char	*dup;
	size_t	word_idx;

	word_idx = 0;
	data->detach = !(is_white(value[0]));
	while (strs[word_idx] != NULL)
	{
		dup = ft_strdup(strs[word_idx]);
		if (dup == NULL)
			return (free_perfectly_split(strs));
		if (link_argv(data, dup))
		{
			free(dup);
			return (free_perfectly_split(strs));
		}
		data->detach = 0;
		word_idx++;
	}
	data->detach = !(is_white(value[ft_strlen(value) - 1]));
	free_perfectly_split(strs);
	return (0);
}

int	process_special_dollar(t_data *data, char *word, size_t *idx)
{
	char	*res;

	res = NULL;
	if (word[*idx] == 0)
		res = make_word(word, idx, 1);
	// else if (word[(*idx)++] == '?')
	// 	res = itoa(0);
	if (res == NULL)
		return (1);
	if (link_argv(data, res))
		return (free_new_argv(res));
	return (0);
}
