/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:01:20 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 13:54:25 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_pattern(char	*pattern, char *fname)
{
	size_t	p_len;
	size_t	f_len;
	size_t	i;
	size_t	skip;

	p_len = ft_strlen(pattern);
	f_len = ft_strlen(fname);
	i = 0;
	while (i < p_len && i < f_len && pattern[i] == fname[i])
		i++;
	if (p_len == i)
		return (i == f_len);
	if (pattern[i] == '*')
	{
		skip = 0;
		while (skip + i <= f_len)
		{
			if (check_pattern(pattern + i + 1, fname + skip + i))
				return (true);
			skip++;
		}
	}
	return (false);
}

t_list	*make_pattern_match_list(char *pattern)
{
	DIR				*dir;
	struct dirent	*file;
	t_list			*tmp;
	t_node			*newnode;

	tmp = ft_lstcreate();
	dir = opendir(".");
	if (!dir)
		return (NULL);
	if (!tmp)
		exit(1);
	file = readdir(dir);
	while (file)
	{
		if (check_pattern(pattern, file->d_name) && *(file->d_name) != '.')
		{
			newnode = ft_lstnew(ft_strdup(file->d_name));
			if (!newnode)
				exit(1);
			ft_lstadd_back(tmp, newnode);
		}
		file = readdir(dir);
	}
	closedir(dir);
	return (tmp);
}

static void	wildcard_handler(t_list *tmp, t_node **cur)
{
	t_node	*dump;
	t_list	*subed;

	subed = make_pattern_match_list((*cur)->content);
	if (subed->head == NULL)
	{
		ft_lstadd_back(tmp, *cur);
		*cur = (*cur)->next;
	}
	else
	{
		ft_lstadd_back(tmp, subed->head);
		while (tmp->tail->next != NULL)
			tmp->tail = tmp->tail->next;
		dump = *cur;
		*cur = (*cur)->next;
		ft_lstdelone(dump);
	}
	free(subed);
}

t_list	*substitute_wilds(t_list *lst)
{
	t_list	*tmp;
	t_node	*cur;

	tmp = ft_lstcreate();
	cur = lst->head;
	while (cur)
	{
		if (is_there_wild(cur->content))
			wildcard_handler(tmp, &cur);
		else
		{
			ft_lstadd_back(tmp, cur);
			cur = cur->next;
		}
	}
	free(lst);
	return (tmp);
}
