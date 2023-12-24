/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 18:05:47 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/19 18:05:48 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo") || \
	!ft_strcmp(cmd, "env") || !ft_strcmp(cmd, "exit") || \
	!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "pwd") || \
	!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

void	exec_builtin(char *cmd, char *argv[], t_envtree *env)
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
