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

static int	*get_fd(void)
{
	static int	fd[2] = {-1, -1};
	
	return (fd);
}

static void	save_fd(int input, int output)
{
	get_fd()[0] = input;
	get_fd()[1] = output;
}

static void	todo_chid(t_tree_node *node, t_envtree *env, int pipe_fd[2], int n)
{
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	if (node->fd[0] != 0)
		dup2(node->fd[0], STDIN_FILENO);
	if (node->fd[1] != 1)
		dup2(node->fd[1], STDOUT_FILENO);
	if (n == 0)
		dup2(get_fd()[1], STDOUT_FILENO);
	if (is_builtin(node->left->contents[0]))
	{
		exec_builtin(node->left->contents[0], node->left->contents, env);
		exit(EXIT_SUCCESS);
	}
	else if (exec_bin(node->left->contents, env))
		exit(EXIT_FAILURE);
}


static void	todo_parent(t_tree_node *node, t_envtree *env, int pipe_fd[2], int n)
{
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	excute_hub(node->left, env, n + 1);
	wait(NULL);
	if (n == 0)
	{
		dup2(get_fd()[0], STDIN_FILENO);
		dup2(get_fd()[1], STDOUT_FILENO);
		save_fd(-1, -1);
	}
}

void	 exec_pipe_cmd(t_tree_node *node, t_envtree *env, int n)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (get_fd()[0] == -1 && get_fd()[1] == -1)
		save_fd(dup(0), dup(1));
	if (pipe(pipe_fd) < 0)
		exit(1);
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		todo_chid(node->right, env, pipe_fd, n);
	else
		todo_parent(node, env, pipe_fd, n);
}
