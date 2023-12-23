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

static void	todo_child(char *argv[], t_envtree *env)
{
	int	ret;

	ret = exec_bin(argv, env);
	exit(ret);
}

static void	todo_parent(pid_t pid)
{
	int status;

	waitpid(pid, &status, WUNTRACED | WCONTINUED);
}

void	exec_single_cmd(t_tree_node *node, t_envtree *env)
{
	int		save_fd[2];
	char	**argv;
	pid_t	pid;

	if (!handle_redir(node->right, node->fd))
		return ;
	argv = node->left->contents;
	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	dup2(node->fd[0], STDIN_FILENO);
	dup2(node->fd[1], STDOUT_FILENO);
	if (is_builtin(argv[0]))
		exec_builtin(argv[0], argv, env);
	else
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			todo_child(argv, env);
		else
			todo_parent(pid);
	}
	reset_io(save_fd);
}
