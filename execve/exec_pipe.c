/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:12:11 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/04 20:12:12 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	todo_chid(t_tree_node *node, t_envtree *env, int pipe_fd[2])
{
	dup2(pipe_fd[1], STDOUT_FILENO);
	close(pipe_fd[0]);
	if (is_builtin(node->left->contents[0]))
		exec_builtin(node->left->contents[0], node->left->contents, env);
	else if (exec_bin(node->left->contents, env))
		exit(EXIT_FAILURE);
}

static void	todo_parent(t_tree_node *node, t_envtree *env, int save_fd[2], int pipe_fd[2])
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	excute_hub(node->left, env);
	close(STDIN_FILENO);
	wait(NULL);
	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
}

void	 exec_pipe_cmd(t_tree_node *node, t_envtree *env)
{
	int		save_fd[2];
	int		pipe_fd[2];
	pid_t	pid;

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	if (pipe(pipe_fd) < 0)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		todo_chid(node->right, env, pipe_fd);
	else
		todo_parent(node, env, save_fd, pipe_fd);
}
