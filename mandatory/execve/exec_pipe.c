/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:12:11 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 21:31:55 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_io(t_tree_node *node, int pipe_fd[2], int saved_fd[2])
{
	if (node->cmd_cnt == 0)
		dup2(saved_fd[1], STDOUT_FILENO);
	else
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (node->fd[0] == -1 || node->fd[1] == -1)
		exit(EXIT_FAILURE);
	if (node->fd[0] != 0)
	{
		dup2(node->fd[0], STDIN_FILENO);
		close(node->fd[0]);
	}
	if (node->fd[1] != 1)
	{
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
	}
}

static void	todo_chid(t_tree_node *node, t_envtree *env, \
						int pipe_fd[2], int saved_fd[2])
{
	int		exit_code;
	char	**argv;

	set_child_signal();
	redirect_io(node, pipe_fd, saved_fd);
	argv = convert_word_lst_to_array(node->left->contents, env);
	if (*argv == NULL)
	{
		free(argv);
		exit(EXIT_SUCCESS);
	}
	if (is_builtin(argv[0]))
	{
		exit_code = exec_builtin_pipe(argv[0], argv, env);
		exit(exit_code);
	}
	exit_code = exec_bin(argv, env);
	free_perfectly_split(argv);
	exit(exit_code);
}

static void	todo_parent(int pipe_fd[2], int n)
{
	if (n != 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
	}
	else
		close(STDIN_FILENO);
}

void	exec_pipe_cmd(t_tree_node *node, t_envtree *env, \
						int saved_fd[2], pid_t *last_pid)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (!handle_other_redirs(node, env))
		return ;
	find_fd(node->right, node->fd);
	if (node->left->contents->head == NULL)
		return ;
	if (node->cmd_cnt != 0)
	{
		if (pipe(pipe_fd) < 0)
			exit(1);
	}
	pid = fork();
	if (pid == -1)
		exit(1);
	if (pid == 0)
		todo_chid(node, env, pipe_fd, saved_fd);
	else
	{
		todo_parent(pipe_fd, node->cmd_cnt);
		if (node->cmd_cnt == 0)
			*last_pid = pid;
	}
}
