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

static int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "env") \
	|| !ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd") \
	|| !ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

static void	exec_builtin(char *cmd, char *argv[], t_envtree *env)
{
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(argv, env);
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(argv);
	if (!ft_strcmp(cmd, "env"))
		ft_env(env->root);
	if (!ft_strcmp(cmd, "exit"))
	{
		printf("exit\n");
		ft_exit();
	}
	if (!ft_strcmp(cmd, "export"))
		ft_export(argv, env);
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(env, argv);
}

int status;

void	exec_last_cmd(char *cmd, char *argv[], t_envtree *env)
{
	char	**envp;
	char	*command;
	pid_t	pid;

	if (!cmd)
		return ;
	envp = make_envp(env);
	command = make_command(cmd, find_envnode(env->root, "PATH"));
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		// redirection 처리
		if (is_builtin(cmd))
		{
			exec_builtin(cmd, argv, env);
			return ;
		}
		execve(command, argv, envp);
		exit(1);
	}
	waitpid(pid, &status, WUNTRACED);
	free(envp);
}

void	exec_multi_cmd(char *cmd, char *argv[], t_envtree *env)
{
	char	**envp;
	char	*command;
	int		fd[2];
	pid_t	pid;

	if (!cmd)
		return ;
	envp = make_envp(env);
	command = make_command(cmd, find_envnode(env->root, "PATH"));
	if (pipe(fd) < 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		// redirection 처리
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
			exit(1);
		if (is_builtin(cmd))
		{
			exec_builtin(cmd, argv, env);
			return ;
		}
		execve(command, argv, envp);
		exit(1);
	}
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		exit(1);
	waitpid(pid, &status, WUNTRACED);
	free(envp);
}
