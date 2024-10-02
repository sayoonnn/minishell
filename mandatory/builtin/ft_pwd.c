/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayoon <sayoon@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:59:00 by sayoon            #+#    #+#             */
/*   Updated: 2023/12/01 18:59:04 by sayoon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, PATH_MAX);
	if (!path)
	{
		ft_printf(2, "minishell: ");
		perror("getcwd: cannot access parent directories");
		free(path);
		return (1);
	}
	printf("%s\n", path);
	free(path);
	return (success);
}
