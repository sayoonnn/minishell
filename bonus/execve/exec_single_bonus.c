/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:12:11 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:43:12 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	todo_child(char *argv[], t_envtree *env)
{
	int	ret;

	set_child_signal();
	ret = exec_bin(argv, env);
	exit(ret);
}

static void	todo_parent(char **argv, int save_fd[2])
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
	free_perfectly_split(argv);
	reset_io(save_fd);
}

static void	change_fd(t_tree_node *node, int save_fd[2])
{
	save_fd[0] = 0;
	save_fd[1] = 1;
	if (node->fd[0] != 0)
	{
		save_fd[0] = dup(STDIN_FILENO);
		dup2(node->fd[0], STDIN_FILENO);
		close(node->fd[0]);
	}
	if (node->fd[1] != 1)
	{
		save_fd[1] = dup(STDOUT_FILENO);
		dup2(node->fd[1], STDOUT_FILENO);
		close(node->fd[1]);
	}
}

static void	excute_command(char **argv, t_envtree *env, int save_fd[2])
{
	pid_t	pid;

	if (is_builtin(argv[0]))
	{
		exec_builtin(argv[0], argv, env);
		reset_io(save_fd);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			todo_child(argv, env);
		else
			todo_parent(argv, save_fd);
	}
}

void	exec_single_cmd(t_tree_node *node, t_envtree *env)
{
	int		save_fd[2];
	char	**argv;

	argv = convert_word_lst_to_array(node->left->contents, env);
	find_fd(node->right, node->fd);
	if (*argv == NULL)
	{
		free(argv);
		g_errcode = 0;
		return ;
	}
	change_fd(node, save_fd);
	excute_command(argv, env, save_fd);
}
