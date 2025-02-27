/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonghopa <jonghopa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 18:59:00 by sayoon            #+#    #+#             */
/*   Updated: 2024/01/05 12:48:12 by jonghopa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
