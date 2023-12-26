/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta_character_convertor_utils.c.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 20:55:06 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 21:12:50 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_new_word(char *word)
{
	free(word);
	return (1);
}

int	link_argv(t_parsing *parsing, char *argv)
{
	char	*res;
	t_node	*new;

	if (argv == NULL)
		return (1);
	if (ft_strlen(argv) == 0)
		free(argv);
	else if (parsing->word_lst->head == 0 || parsing->detach == 0)
	{
		new = ft_lstnew(argv);
		if (new == NULL)
			return (free_new_word(argv));
		ft_lstadd_back(parsing->word_lst, new);
		parsing->detach = 1;
	}
	else if (parsing->detach)
	{
		res = ft_strjoin(parsing->word_lst->tail->content, argv);
		if (res == NULL)
			return (free_new_word(argv));
		free(parsing->word_lst->tail->content);
		free(argv);
		parsing->word_lst->tail->content = res;
	}
	return (0);
}

int	link_argv_to_word_lst(t_parsing *parsing, char **strs, char *value)
{
	char	*copy;
	size_t	word_idx;

	word_idx = 0;
	parsing->detach = !(is_white(value[0]));
	while (strs[word_idx] != NULL)
	{
		copy = ft_strdup(strs[word_idx]);
		if (copy == NULL)
			return (free_perfectly_split(strs));
		if (link_argv(parsing, copy))
		{
			free(copy);
			return (free_perfectly_split(strs));
		}
		parsing->detach = 0;
		word_idx++;
	}
	parsing->detach = !(is_white(value[ft_strlen(value) - 1]));
	free_perfectly_split(strs);
	return (0);
}
