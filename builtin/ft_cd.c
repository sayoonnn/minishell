/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 20:45:24 by sayoon            #+#    #+#             */
/*   Updated: 2023/11/30 20:45:25 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_envtree *env)
{
	t_envnode	*tmp;
	char		*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		exit(1);
	tmp = find_envnode(env->root, "HOME");
	if (!tmp)
	{
		print_err("cd", "no home directory");
		return (fail);
	}
	if (chdir(tmp->value) < 0)
	{
		print_err_builtin("cd", ERR_NO_DIR_FILE, tmp->value);
		return (fail);
	}
	add_env(env, make_envnode("OLDPWD", pwd));
	free(pwd);
	return (success);
}

static int	cd_oldpwd(t_envtree *env)
{
	t_envnode	*old;
	char		*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
		exit(1);
	old = find_envnode(env->root, "OLDPWD");
	if (old)
	{
		if (chdir(old->value) < 0)
		{
			print_err_builtin("cd", ERR_NO_DIR_FILE, old->value);
			return (fail);
		}
	}
	printf("%s\n", old->value);
	add_env(env, make_envnode("OLDPWD", pwd));
	free(pwd);
	return (success);
}

int	ft_cd(char *arg[], t_envtree *env)
{
	char	*cur;

	cur = getcwd(NULL, PATH_MAX);
	if (!cur)
		exit(1);
	if (arg[1] == NULL || !ft_strncmp(arg[1], "~", 2))
		return (cd_home(env));
	else if (!ft_strncmp(arg[1], "-", 2))
		return (cd_oldpwd(env));
	else
	{
		if (chdir(arg[1]) < 0)
		{
			print_err_builtin("cd", ERR_NO_DIR_FILE, arg[1]);
			return (fail);
		}
		add_env(env, make_envnode("OLDPWD", cur));
		free(cur);
	}
	return (success);
}
