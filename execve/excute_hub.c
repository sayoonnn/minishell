/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_hub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:00:10 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 21:27:48 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_redir_exec_single(t_tree_node *node, t_envtree *env)
{
	if (!handle_other_redir(node->right, env))
	{
		g_errcode = 1;
		return ;
	}
	exec_single_cmd(node, env);
}

static void	reset_iofd(int saved_fd[2], pid_t last_pid)
{
	signal(SIGINT, SIG_IGN);
	waitpid(last_pid, &g_errcode, 0);
	while (wait(NULL) != -1)
		;
	if (WIFSIGNALED(g_errcode))
	{
		if (WTERMSIG(g_errcode) == SIGQUIT)
			printf("Quit: 3");
		printf("\n");
		g_errcode = (128 + WTERMSIG(g_errcode));
	}
	else
		g_errcode = WEXITSTATUS(g_errcode);
	dup2(saved_fd[0], STDIN_FILENO);
	dup2(saved_fd[1], STDOUT_FILENO);
	close(saved_fd[0]);
	close(saved_fd[1]);
	saved_fd[0] = -1;
	saved_fd[1] = -1;
	set_signal();
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
		exec_pipe_cmd(node->right, env, saved_fd, &last_pid);
	}
	else
	{
		exec_pipe_cmd(node->left, env, saved_fd, &last_pid);
		exec_pipe_cmd(node->right, env, saved_fd, &last_pid);
	}
	if (n == 0)
		reset_iofd(saved_fd, last_pid);
}

void	excute_hub(t_tree_node *root, t_envtree *env)
{
	if (root == NULL)
		return ;
	if (!handle_heredoc_first(root, env))
		return ;
	if (root->token_type == CMD)
		sub_redir_exec_single(root, env);
	else
		sub_redir_exec_pipe(root, env, 0);
}
