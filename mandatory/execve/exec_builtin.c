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
		g_errcode = ft_cd(argv);
	if (!ft_strcmp(cmd, "echo"))
		g_errcode = ft_echo(argv);
	if (!ft_strcmp(cmd, "env"))
		g_errcode = ft_env(env->root);
	if (!ft_strcmp(cmd, "exit"))
		g_errcode = ft_exit(argv, false);
	if (!ft_strcmp(cmd, "export"))
		g_errcode = ft_export(argv, env);
	if (!ft_strcmp(cmd, "pwd"))
		g_errcode = ft_pwd();
	if (!ft_strcmp(cmd, "unset"))
		g_errcode = ft_unset(env, argv);
	free_perfectly_split(argv);
}

int	exec_builtin_pipe(char *cmd, char *argv[], t_envtree *env)
{
	int	ret;

	if (!ft_strcmp(cmd, "cd"))
		ret = ft_cd(argv);
	if (!ft_strcmp(cmd, "echo"))
		ret = ft_echo(argv);
	if (!ft_strcmp(cmd, "env"))
		ret = ft_env(env->root);
	if (!ft_strcmp(cmd, "exit"))
		ft_exit(argv, true);
	if (!ft_strcmp(cmd, "export"))
		ret = ft_export(argv, env);
	if (!ft_strcmp(cmd, "pwd"))
		ret = ft_pwd();
	if (!ft_strcmp(cmd, "unset"))
		ret = ft_unset(env, argv);
	free_perfectly_split(argv);
	return (ret);
}
