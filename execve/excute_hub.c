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

void	sub_redir_exec(t_tree_node *node, t_envtree *env, int is_pipe)
{
	node->fd[0] = 0;
	node->fd[1] = 1;
	if (!handle_redir(node->right, node->fd))
		return ;
	if (is_pipe)
		exec_pipe_cmd(node, env);
	else
		exec_single_cmd(node, env);
}

void	excute_hub(t_tree_node *pt, t_envtree *env)
{
	static int	is_pipe = false;

	if (pt->token_type == PIPELINE)
	{
		is_pipe = true;
		excute_hub(pt->left, env);
		sub_redir_exec(pt->right, env, is_pipe);
		is_pipe = false;
	}
	if (pt->token_type == CMD)
		sub_redir_exec(pt, env, is_pipe);

}
