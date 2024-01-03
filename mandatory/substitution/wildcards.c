/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 12:01:20 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/03 12:01:22 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_pattern(char	*pattern, char *fname)
{
	size_t	p_len;
	size_t	f_len;
	size_t	i;
	size_t	skip;
	char	**cache;

	p_len = ft_strlen(pattern);
	f_len = ft_strlen(fname);
	i = 0;
	while (i < p_len && i < f_len && pattern[i] == fname[i])
		i++;
	if (p_len == i)
		return (true);
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
	struct dirent	*cur_file;
	t_list			*tmp;
	t_node			*newnode;

	tmp = ft_lstcreate();
	dir = opendir(".");
	if (!dir)
		return (NULL);
	cur_file = readdir(dir);
	while (cur_file)
	{
		if (check_pattern(pattern, cur_file->d_name))
		{
			newnode = ft_lstnew(ft_strdup(cur_file->d_name));
			if (!newnode)
				exit(1);
			ft_lstadd_back(tmp, newnode);
		}
		cur_file = readdir(dir);
	}
	closedir(dir);
	return (tmp);
}
