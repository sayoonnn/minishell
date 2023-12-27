/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:00:26 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 21:22:14 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	substitute_word(t_parsing *parsing, t_envtree *env, char *content)
{
	size_t	idx;

	idx = 0;
	while (content[idx] != 0)
	{
		if (is_quote(content[idx]))
		{
			if (handle_word_with_qts(parsing, env, content, &idx))
				return (1);
			continue ;
		}
		if (handle_wd(parsing, env, content, &idx))
			return (1);
	}
	return (0);
}

int	substitute_words(t_parsing *parsing, t_envtree *env, t_list *contents)
{
	t_node	*ptr;

	ptr = contents->head;
	while (ptr != NULL)
	{
		if (substitute_word(parsing, env, ptr->content))
			return (1);
		parsing->detach = 0;
		ptr = ptr->next;
	}
	return (0);
}

char	**convert_word_lst_to_array(t_list *lst)
{
	t_node			*ptr;
	char			**words;
	unsigned int	cnt;
	unsigned int	idx;

	cnt = 0;
	ptr = lst->head;
	while (ptr != NULL)
	{
		cnt++;
		ptr = ptr->next;
	}
	words = (char **)malloc(sizeof(char *) * (cnt + 1));
	if (words == NULL)
		return (NULL);
	ptr = lst->head;
	idx = 0;
	while (ptr != NULL)
	{
		words[idx++] = ptr->content;
		lst->head = ptr->next;
		free(ptr);
		ptr = lst->head;
	}
	lst->tail = NULL;
	words[idx] = NULL;
	return (words);
}

int	convert_content_to_argv(t_parsing *ps, t_envtree *env, t_list *contents)
{
	if (substitute_words(ps, env, contents))
		return (1);
	if (convert_word_lst_to_array(ps->word_lst))
		return (1);
	return (0);
}
