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
#define PATH_MAX 4096

static void	cd_home(t_envnode *env)
{
	t_envnode	*home;

	home = find_envnode(env, "HOME");
	if (!home)
	{
		//에러설정
		printf("home?\n");
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
	if (arg[1] == NULL || !ft_strcmp(arg[1], "~"))
		cd_home(env);
	else if (!ft_strcmp(arg[1], "-"))
		cd_oldpwd(env);
	if (chdir(arg[1]) < 0)
		// bash: cd: /home/sayon/dfijos: No such file or directory
		// errno 설정
	return ;
}
