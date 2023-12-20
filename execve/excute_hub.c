/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:00:10 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 16:00:10 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	excute_command(t_tree_node *pt, t_envtree *env);
// static void	excute_redir(t_tree_node *pt, t_envtree *env);

void	excute_hub(t_tree_node *pt, t_envtree *env)
{
	static int	fd[2];
	fd[0] = 0;
	fd[1] = 1;

	if (pt->token_type == CMD)
		exec_single_cmd(pt->left->contents, env, fd);
	}
}
