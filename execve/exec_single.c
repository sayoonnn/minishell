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

void	exec_single_cmd(char *argv[], t_envtree *env, int fd[2])
{
	int		save[2];
	pid_t	pid;

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	dup2(fd[0], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
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
	reset_io(save);
}
