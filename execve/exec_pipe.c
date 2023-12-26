/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:12:11 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/26 16:15:44 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	todo_chid(t_tree_node *node, t_envtree *env, int pipe_fd[2], int n)
{
	if (n == 0)
		dup2(get_fd()[1], STDOUT_FILENO);
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
	}
	if (node->fd[0] == -1 || node->fd[1] == -1)
		exit(EXIT_FAILURE);
	if (node->fd[0] != 0)
		dup2(node->fd[0], STDIN_FILENO);
	if (node->fd[1] != 1)
		dup2(node->fd[1], STDOUT_FILENO);
	if (is_builtin(node->left->contents[0]))
	{
		exec_builtin(node->left->contents, node->left->contents, env);
		exit(EXIT_SUCCESS);
	}
	else if (exec_bin(node->left->contents, env))
		exit(EXIT_FAILURE);
}

void	exec_pipe_cmd(t_tree_node *node, t_envtree *env, int n)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (n != 0)
	{
		if (pipe(pipe_fd) < 0)
			exit(1);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		todo_chid(node, env, pipe_fd, n);
	else
	{
		if (n != 0)
		{
			close(pipe_fd[1]);
			dup2(pipe_fd[0], STDIN_FILENO);
		}
	}
}
