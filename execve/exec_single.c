/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: devpark <devpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:12:11 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/01 21:07:22 by devpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	todo_child(char *argv[], t_envtree *env)
{
	int	ret;

	set_child_signal();
	ret = exec_bin(argv, env);
	exit(ret);
}

static void	todo_parent(void)
{
	signal(SIGINT, SIG_IGN);
	wait(&g_errcode);
	if (WIFSIGNALED(g_errcode))
	{
		if (WTERMSIG(g_errcode) == SIGQUIT)
			printf("Quit: 3");
		printf("\n");
		g_errcode = (128 + WTERMSIG(g_errcode));
	}
	else
		g_errcode = WEXITSTATUS(g_errcode);
	set_signal();
}

static void	change_fd(t_tree_node *node, int save_fd[2])
{
	find_fd(node->right, node->fd);
	if (node->fd[0] != 0)
	{
		save_fd[0] = dup(STDIN_FILENO);
		dup2(node->fd[0], STDIN_FILENO);
	}
	if (node->fd[1] != 1)
	{
		save_fd[1] = dup(STDOUT_FILENO);
		dup2(node->fd[1], STDOUT_FILENO);
	}
}

void	exec_single_cmd(t_tree_node *node, t_envtree *env)
{
	int		save_fd[2];
	char	**argv;
	pid_t	pid;

	argv = convert_word_lst_to_array(node->contents);
	if (*argv == NULL)
		return ;
	change_fd(node, save_fd);
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
			todo_parent();
	}
	free_arr(argv);
	reset_io(save_fd);
}
