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

int	*get_fd(void)
{
	static int	fd[2] = {-1, -1};

	return (fd);
}

void	save_fd(int input, int output)
{
	get_fd()[0] = input;
	get_fd()[1] = output;
}

void	sub_redir_exec_single(t_tree_node *node, t_envtree *env)
{
	node->fd[0] = 0;
	node->fd[1] = 1;
	if (!handle_redir(node->right, node->fd))
		return ;
	exec_single_cmd(node, env);
}

void	sub_redir_exec_pipe(t_tree_node *node, t_envtree *env, int n)
{
	if (get_fd()[0] == -1 && get_fd()[1] == -1)
		save_fd(dup(STDIN_FILENO), dup(STDOUT_FILENO));
	if (node->left->token_type == PIPELINE)
	{
		sub_redir_exec_pipe(node->left, env, n + 1);
		exec_pipe_cmd(node->right, env, n);
	}
	else
	{
		exec_pipe_cmd(node->left, env, n + 1);
		exec_pipe_cmd(node->right, env, n);
	}
	if (n == 0)
	{
		while (waitpid(-1, NULL, 0) != -1)
			;
		dup2(get_fd()[0], STDIN_FILENO);
		dup2(get_fd()[1], STDOUT_FILENO);
		save_fd(-1, -1);
	}
}

void	excute_hub(t_tree_node *pt, t_envtree *env)
{
	if (pt->token_type == CMD)
		sub_redir_exec_single(pt, env);
	else
	{
		trave_redir(pt);
		sub_redir_exec_pipe(pt, env, 0);
	}
}
