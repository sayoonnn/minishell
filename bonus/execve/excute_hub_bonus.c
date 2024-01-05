/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_hub_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:00:10 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:42:46 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	sub_redir_exec_single(t_tree_node *node, t_envtree *env)
{
	if (!handle_other_redir(node->right, env))
	{
		g_errcode = 1;
		return ;
	}
	exec_single_cmd(node, env);
}

void	sub_redir_exec_pipe(t_tree_node *node, t_envtree *env, int n)
{
	static int		saved_fd[2] = {-1, -1};
	static pid_t	last_pid = -1;

	if (saved_fd[0] == -1 && saved_fd[1] == -1)
	{
		saved_fd[0] = dup(STDIN_FILENO);
		saved_fd[1] = dup(STDOUT_FILENO);
	}
	if (node->left->token_type == PIPE)
	{
		sub_redir_exec_pipe(node->left, env, n + 1);
		node->right->cmd_cnt = n;
		exec_pipe_cmd(node->right, env, saved_fd, &last_pid);
	}
	else
	{
		node->left->cmd_cnt = n + 1;
		exec_pipe_cmd(node->left, env, saved_fd, &last_pid);
		node->right->cmd_cnt = n;
		exec_pipe_cmd(node->right, env, saved_fd, &last_pid);
	}
	if (n == 0)
		undo_setting(saved_fd, last_pid, node);
}

static void	excute_list(t_tree_node *root, t_envtree *env)
{
	if (root->token_type == AND)
	{
		excute_hub(root->left, env);
		if (!g_errcode)
			excute_hub(root->right, env);
	}
	else if (root->token_type == OR)
	{
		excute_hub(root->left, env);
		if (g_errcode)
			excute_hub(root->right, env);
	}
}

void	excute_hub(t_tree_node *root, t_envtree *env)
{
	if (root == NULL)
		return ;
	if (!handle_heredoc_first(root, env))
		return ;
	if (root->token_type == CMD)
		sub_redir_exec_single(root, env);
	else if (root->token_type == PIPE)
		sub_redir_exec_pipe(root, env, 0);
	else if (root->token_type == AND || root->token_type == OR)
		excute_list(root, env);
	else if (root->token_type == SUBSHELL)
		excute_hub(root->mid, env);
}
