/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:10:15 by jonghopa          #+#    #+#             */
/*   Updated: 2024/01/02 00:24:27 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_tree_bonus.h"

t_parsing	*init_parsing_tool(void)
{
	t_parsing	*parsing;

	parsing = (t_parsing *)malloc(sizeof(t_parsing));
	if (parsing == NULL)
		exit(1);
	parsing->tokens = deque_create();
	if (parsing->tokens == NULL)
		exit(1);
	parsing->cmd_flag = 0;
	parsing->subsh_cnt = 0;
	parsing->root = NULL;
	parsing->cmd_info_ptr = NULL;
	return (parsing);
}
