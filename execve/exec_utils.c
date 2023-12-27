/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 14:56:33 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/05 14:56:33 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*make_binpath(char *cmd, t_envnode *path_node)
{
	int			i;
	char		**path;
	char		*tmp;
	char		*command;

	if (!path_node || path_node->value == NULL)
		return (NULL);
	path = ft_oldsplit(path_node->value, ':');
	tmp = ft_strjoin("/", cmd);
	i = -1;
	while (path[++i])
	{
		command = ft_strjoin(path[i], tmp);
		if (!access(command, F_OK))
		{
			free(tmp);
			free_arr(path);
			return (command);
		}
		free(command);
	}
	free(tmp);
	free_arr(path);
	return (NULL);
}
