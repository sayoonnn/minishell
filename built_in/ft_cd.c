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

//#include "minishell.h"
#include "env_tree.h"
#include <limits.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static void	cd_home(t_envnode *env)
{
	t_envnode	*home;

	home = find_envnode(env, "HOME");
	if (!home)
	{
		//에러설정
		return ;
	}
	if (chdir(home->value) < 0)
	{
		// 에러 설정
		return ;
	}
}

static void	cd_oldpwd(t_envnode *env)
{
	t_envnode	*old;
	char		*pwd;

	pwd = getcwd(NULL, PATH_MAX);
	if (!pwd)
	{
		//에러 설정
		exit(1) ;
	}
	old = find_envnode(env, "OLDPWD");
	if (!old)
	{
		add_envnode(env, make_envnode("OLDPWD", pwd));
		printf("%s\n", pwd);
		free(pwd);
		return ;
	}
	printf("%s\n", old->value);
	if (chdir(old->value) < 0)
		return ;
	free(old->value);
	old->value = pwd;
	return ;
}

void	ft_cd(char *arg[], t_envnode *env)
{
	char		buffer[PATH_MAX];
	t_envnode	*tmp;

	if (arg[1] == NULL || !ft_strncmp(arg[1], "~", 1))
		cd_home(env);
	else if (!ft_strncmp(arg[1], "-", 1))
		cd_oldpwd(env);
	if (chdir(arg[1]) < 0)
		// bash: cd: /home/sayon/dfijos: No such file or directory
		// errno 설정
	return ;
}
