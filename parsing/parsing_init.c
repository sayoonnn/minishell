/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:10:15 by jonghopa          #+#    #+#             */
/*   Updated: 2023/12/26 14:35:59 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree.h"

t_parsing	*init_parsing_tool(void)
{
	t_parsing	*parsing;

	parsing = (t_parsing *)malloc(sizeof(t_parsing));
	if (parsing == NULL)
		exit(1);
	parsing->tokens = deque_create();
	parsing->argv_lst = ft_lstcreate();
	if (!(parsing->tokens) || !(parsing->argv_lst))
		exit(1);
	parsing->detach = 0;
	parsing->cmd_flag = 0;
	parsing->root = NULL;
	parsing->cmd_info_ptr = NULL;
	return (parsing);
}
