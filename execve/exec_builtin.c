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
		err_code = ft_cd(argv, env) << 8;
	if (!ft_strcmp(cmd, "echo"))
		err_code = ft_echo(argv) << 8;
	if (!ft_strcmp(cmd, "env"))
		err_code = ft_env(env->root) << 8;
	if (!ft_strcmp(cmd, "exit"))
		err_code = ft_exit(argv) << 8;
	if (!ft_strcmp(cmd, "export"))
		err_code = ft_export(argv, env) << 8;
	if (!ft_strcmp(cmd, "pwd"))
		err_code = ft_pwd() << 8;
	if (!ft_strcmp(cmd, "unset"))
		err_code = ft_unset(env, argv) << 8;
}

int	exec_builtin_pipe(char *cmd, char *argv[], t_envtree *env)
{
	int	ret;

	if (!ft_strcmp(cmd, "cd"))
		ret = ft_cd(argv, env);
	if (!ft_strcmp(cmd, "echo"))
		ret = ft_echo(argv);
	if (!ft_strcmp(cmd, "env"))
		ret = ft_env(env->root);
	if (!ft_strcmp(cmd, "exit"))
		ret = ft_exit(argv);
	if (!ft_strcmp(cmd, "export"))
		ret = ft_export(argv, env);
	if (!ft_strcmp(cmd, "pwd"))
		ret = ft_pwd();
	if (!ft_strcmp(cmd, "unset"))
		ret = ft_unset(env, argv);
	return (ret);
}
