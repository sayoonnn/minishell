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

#ifndef PATH_MAX
# define PATH_MAX 1024
#endif

static int	is_directory(char *dir)
{
	struct stat	file_info;

	if (stat(dir, &file_info) == -1)
		return (false);
	if (S_ISDIR(file_info.st_mode))
		return (true);
	return (false);
}

static void	print_errs(char *dir)
{
	if (access(dir, F_OK) < 0)
		ft_printf(2, "minishell: cd: %s: %s\n", dir, ERR_NO_DIR_FILE);
	else if (!is_directory(dir))
		ft_printf(2, "minishell: cd: %s: Not a directory\n", dir);
	else if (access(dir, X_OK | W_OK | R_OK) < 0)
		ft_printf(2, "minishell: cd: %s: Permission denied\n", dir);
	else
		ft_printf(2, "minishell: cd: %s: %s\n", dir, ERR_NO_DIR_FILE);
}

int	ft_cd(char *arg[])
{
	char	*cur;
	int		status;

	if (arg[1] == NULL)
		return (success);
	status = success;
	cur = getcwd(NULL, PATH_MAX);
	if (!cur)
		exit(1);
	if (ft_strlen(arg[1]) > PATH_MAX)
	{
		ft_printf(2, "minishell: cd: %s: File name too long\n", arg[1]);
		status = fail;
	}
	else if (chdir(arg[1]) < 0)
	{
		print_errs(arg[1]);
		status = fail;
	}
	free(cur);
	return (status);
}
