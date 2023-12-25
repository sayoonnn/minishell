/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_argv_analyzer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:00:26 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/20 13:43:46 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

int	analyze_cmd_argv(t_data *data, char *word)
{
	t_argv	*new;
	char	*dup;

	dup = ft_strdup(word);
	new = ft_lstnew(dup);
	if (dup == NULL || new == NULL)
	{
		if (dup)
			free(dup);
		return (1);
	}
	ft_lstadd_back(data->argv_lst, new);
	return (0);
}
