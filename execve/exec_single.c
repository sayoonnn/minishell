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

	set_child_signal();
	ret = exec_bin(argv, env);
	exit(ret);
}

static void	todo_parent(pid_t pid)
{	
	(void)pid;
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

static void	find_fd(t_tree_node *node, int fd[2])
{
	if (node == NULL)
		return ;
	if (node->token_type == REDIRECTION_INFO)
	{
		fd[0] = node->fd[0];
		fd[1] = node->fd[1];
	}
	find_fd(node->left, fd);
	find_fd(node->right, fd);
}

void	exec_single_cmd(t_tree_node *node, t_envtree *env, t_list *lst)
{
	int		save_fd[2];
	char	**argv;
	pid_t	pid;

	argv = convert_word_lst_to_array(lst);
	find_fd(node->right, node->fd);
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
