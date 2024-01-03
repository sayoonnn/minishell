/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 16:51:50 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/19 16:51:52 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path(char *cmd, t_envtree *env)
{
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	else
		return (make_binpath(cmd, find_envnode(env->root, "PATH")));
}

static int	is_directory(char *bin_path)
{
	struct stat	file_info;

	if (stat(bin_path, &file_info) == -1)
		exit(1);
	if (S_ISDIR(file_info.st_mode))
		return (1);
	return (0);
}

static int	check_err(char *bin_path, char *cmd)
{
	if (bin_path == NULL)
	{
		ft_printf(2, "minishell: %s: %s\n", cmd, ERR_CMD_NOT_FOUND);
		return (CODE_CMD_NOT_FOUND);
	}
	else if (access(bin_path, F_OK))
	{
		ft_printf(2, "minishell: %s: %s\n", cmd, ERR_NO_DIR_FILE);
		return (CODE_CMD_NOT_FOUND);
	}
	else if (is_directory(bin_path))
	{
		ft_printf(2, "minishell: %s: %s\n", bin_path, "is directory");
		return (CODE_PERM_DENIED);
	}
	else if (access(bin_path, X_OK) != 0)
	{
		ft_printf(2, "minishell: %s: %s\n", bin_path, "permission denied");
		return (CODE_PERM_DENIED);
	}
	return (success);
}

int	exec_bin(char **argv, t_envtree *env)
{
	int		ret;
	char	*bin_path;
	char	**envp;

	bin_path = find_path(argv[0], env);
	ret = check_err(bin_path, argv[0]);
	if (ret)
	{
		free(bin_path);
		return (ret);
	}
	envp = tree_2_envp(env);
	if (execve(bin_path, argv, envp) == -1)
		return (CODE_PERM_DENIED);
	free(bin_path);
	return (success);
}
